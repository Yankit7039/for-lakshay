import { items, users, type User, type InsertUser, type Item, type InsertItem } from "@shared/schema";

export interface IStorage {
  // User methods
  getUser(id: number): Promise<User | undefined>;
  getUserByUsername(username: string): Promise<User | undefined>;
  createUser(user: InsertUser): Promise<User>;
  
  // Item methods
  getItems(userId?: number): Promise<Item[]>;
  getItem(id: number): Promise<Item | undefined>;
  createItem(item: InsertItem): Promise<Item>;
  updateItem(id: number, item: Partial<InsertItem>): Promise<Item | undefined>;
  deleteItem(id: number): Promise<boolean>;
  searchItems(query: string, userId?: number): Promise<Item[]>;
  getItemsByType(type: string, userId?: number): Promise<Item[]>;
}

export class MemStorage implements IStorage {
  private users: Map<number, User>;
  private items: Map<number, Item>;
  private currentUserId: number;
  private currentItemId: number;

  constructor() {
    this.users = new Map();
    this.items = new Map();
    this.currentUserId = 1;
    this.currentItemId = 1;
    
    // Initialize with some sample data
    this.initializeSampleData();
  }

  private initializeSampleData() {
    // Add sample items
    const sampleItems: Omit<Item, 'id'>[] = [
      {
        name: "Premium Running Shoes",
        type: "shoes",
        condition: "new",
        description: "Professional-grade running shoes designed for maximum performance and comfort during intensive training sessions. Features advanced cushioning technology, breathable mesh upper, and durable rubber outsole for superior traction on various surfaces.",
        coverImage: "https://images.unsplash.com/photo-1542291026-7eec264c27ff",
        additionalImages: [
          "https://images.unsplash.com/photo-1549298916-b41d501d3772",
          "https://images.unsplash.com/photo-1525966222134-fcfa99b8ae77"
        ],
        dateAdded: new Date(Date.now() - 2 * 24 * 60 * 60 * 1000), // 2 days ago
        userId: null,
      },
      {
        name: "Classic Denim Shirt",
        type: "shirt",
        condition: "new",
        description: "Timeless denim shirt with premium cotton blend, perfect for casual outings and smart-casual occasions.",
        coverImage: "https://images.unsplash.com/photo-1553062407-98eeb64c6a62",
        additionalImages: [],
        dateAdded: new Date(Date.now() - 7 * 24 * 60 * 60 * 1000), // 1 week ago
        userId: null,
      },
      {
        name: "Formal Business Trousers",
        type: "pant",
        condition: "new",
        description: "Elegant formal trousers crafted from premium wool blend, ideal for business meetings and formal events.",
        coverImage: "https://images.unsplash.com/photo-1594938298603-c8148c4dae35",
        additionalImages: [],
        dateAdded: new Date(Date.now() - 3 * 24 * 60 * 60 * 1000), // 3 days ago
        userId: null,
      },
      {
        name: "Professional Tennis Racket",
        type: "sports-gear",
        condition: "new",
        description: "High-performance tennis racket with advanced carbon fiber construction for competitive players and enthusiasts.",
        coverImage: "https://images.unsplash.com/photo-1622279457486-62dcc4a431d6",
        additionalImages: [],
        dateAdded: new Date(Date.now() - 5 * 24 * 60 * 60 * 1000), // 5 days ago
        userId: null,
      }
    ];

    sampleItems.forEach(item => {
      const id = this.currentItemId++;
      this.items.set(id, { ...item, id });
    });
  }

  // User methods
  async getUser(id: number): Promise<User | undefined> {
    return this.users.get(id);
  }

  async getUserByUsername(username: string): Promise<User | undefined> {
    return Array.from(this.users.values()).find(
      (user) => user.username === username,
    );
  }

  async createUser(insertUser: InsertUser): Promise<User> {
    const id = this.currentUserId++;
    const user: User = { ...insertUser, id };
    this.users.set(id, user);
    return user;
  }

  // Item methods
  async getItems(userId?: number): Promise<Item[]> {
    const allItems = Array.from(this.items.values());
    if (userId !== undefined) {
      return allItems.filter(item => item.userId === userId);
    }
    return allItems.sort((a, b) => new Date(b.dateAdded).getTime() - new Date(a.dateAdded).getTime());
  }

  async getItem(id: number): Promise<Item | undefined> {
    return this.items.get(id);
  }

  async createItem(insertItem: InsertItem): Promise<Item> {
    const id = this.currentItemId++;
    const item: Item = {
      id,
      name: insertItem.name,
      type: insertItem.type,
      condition: insertItem.condition,
      description: insertItem.description || null,
      coverImage: insertItem.coverImage || null,
      additionalImages: insertItem.additionalImages || null,
      dateAdded: new Date(),
      userId: null,
    };
    this.items.set(id, item);
    return item;
  }

  async updateItem(id: number, updateData: Partial<InsertItem>): Promise<Item | undefined> {
    const existingItem = this.items.get(id);
    if (!existingItem) {
      return undefined;
    }
    
    const updatedItem: Item = {
      ...existingItem,
      ...updateData,
    };
    
    this.items.set(id, updatedItem);
    return updatedItem;
  }

  async deleteItem(id: number): Promise<boolean> {
    return this.items.delete(id);
  }

  async searchItems(query: string, userId?: number): Promise<Item[]> {
    const items = await this.getItems(userId);
    const lowercaseQuery = query.toLowerCase();
    
    return items.filter(item =>
      item.name.toLowerCase().includes(lowercaseQuery) ||
      item.description?.toLowerCase().includes(lowercaseQuery) ||
      item.type.toLowerCase().includes(lowercaseQuery)
    );
  }

  async getItemsByType(type: string, userId?: number): Promise<Item[]> {
    const items = await this.getItems(userId);
    return items.filter(item => item.type === type);
  }
}

export const storage = new MemStorage();
