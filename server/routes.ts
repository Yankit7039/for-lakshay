import type { Express } from "express";
import { createServer, type Server } from "http";
import { storage } from "./storage";
import { insertItemSchema } from "@shared/schema";
import { z } from "zod";

export async function registerRoutes(app: Express): Promise<Server> {
  // Get all items
  app.get("/api/items", async (req, res) => {
    try {
      const { search, type } = req.query;
      
      let items;
      if (search && typeof search === 'string') {
        items = await storage.searchItems(search);
      } else if (type && typeof type === 'string') {
        items = await storage.getItemsByType(type);
      } else {
        items = await storage.getItems();
      }
      
      res.json(items);
    } catch (error) {
      console.error('Error fetching items:', error);
      res.status(500).json({ message: "Failed to fetch items" });
    }
  });

  // Get single item
  app.get("/api/items/:id", async (req, res) => {
    try {
      const id = parseInt(req.params.id);
      const item = await storage.getItem(id);
      
      if (!item) {
        return res.status(404).json({ message: "Item not found" });
      }
      
      res.json(item);
    } catch (error) {
      console.error('Error fetching item:', error);
      res.status(500).json({ message: "Failed to fetch item" });
    }
  });

  // Create new item
  app.post("/api/items", async (req, res) => {
    try {
      const validatedData = insertItemSchema.parse(req.body);
      const newItem = await storage.createItem(validatedData);
      
      res.status(201).json(newItem);
    } catch (error) {
      if (error instanceof z.ZodError) {
        return res.status(400).json({ 
          message: "Validation error", 
          errors: error.errors 
        });
      }
      
      console.error('Error creating item:', error);
      res.status(500).json({ message: "Failed to create item" });
    }
  });

  // Update item
  app.put("/api/items/:id", async (req, res) => {
    try {
      const id = parseInt(req.params.id);
      const validatedData = insertItemSchema.partial().parse(req.body);
      
      const updatedItem = await storage.updateItem(id, validatedData);
      
      if (!updatedItem) {
        return res.status(404).json({ message: "Item not found" });
      }
      
      res.json(updatedItem);
    } catch (error) {
      if (error instanceof z.ZodError) {
        return res.status(400).json({ 
          message: "Validation error", 
          errors: error.errors 
        });
      }
      
      console.error('Error updating item:', error);
      res.status(500).json({ message: "Failed to update item" });
    }
  });

  // Delete item
  app.delete("/api/items/:id", async (req, res) => {
    try {
      const id = parseInt(req.params.id);
      const deleted = await storage.deleteItem(id);
      
      if (!deleted) {
        return res.status(404).json({ message: "Item not found" });
      }
      
      res.json({ message: "Item deleted successfully" });
    } catch (error) {
      console.error('Error deleting item:', error);
      res.status(500).json({ message: "Failed to delete item" });
    }
  });

  // Get item statistics
  app.get("/api/stats", async (req, res) => {
    try {
      const items = await storage.getItems();
      const weekAgo = new Date();
      weekAgo.setDate(weekAgo.getDate() - 7);
      
      const stats = {
        totalItems: items.length,
        categories: new Set(items.map(item => item.type)).size,
        recentAdditions: items.filter(item => 
          new Date(item.dateAdded) > weekAgo
        ).length
      };
      
      res.json(stats);
    } catch (error) {
      console.error('Error fetching stats:', error);
      res.status(500).json({ message: "Failed to fetch statistics" });
    }
  });

  const httpServer = createServer(app);
  return httpServer;
}
