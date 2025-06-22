import { pgTable, text, serial, integer, boolean, timestamp } from "drizzle-orm/pg-core";
import { createInsertSchema } from "drizzle-zod";
import { z } from "zod";

export const users = pgTable("users", {
  id: serial("id").primaryKey(),
  username: text("username").notNull().unique(),
  password: text("password").notNull(),
});

export const items = pgTable("items", {
  id: serial("id").primaryKey(),
  name: text("name").notNull(),
  type: text("type").notNull(),
  condition: text("condition").notNull().default("new"),
  description: text("description"),
  coverImage: text("cover_image"),
  additionalImages: text("additional_images").array(),
  dateAdded: timestamp("date_added").notNull().defaultNow(),
  userId: integer("user_id").references(() => users.id),
});

export const insertUserSchema = createInsertSchema(users).pick({
  username: true,
  password: true,
});

export const insertItemSchema = createInsertSchema(items).omit({
  id: true,
  dateAdded: true,
  userId: true,
}).extend({
  name: z.string().min(1, "Item name is required"),
  type: z.string().min(1, "Item type is required"),
  condition: z.string().default("new"),
  description: z.string().optional(),
  coverImage: z.string().optional(),
  additionalImages: z.array(z.string()).optional(),
});

export type InsertUser = z.infer<typeof insertUserSchema>;
export type User = typeof users.$inferSelect;
export type InsertItem = z.infer<typeof insertItemSchema>;
export type Item = typeof items.$inferSelect;

// Item type options
export const ITEM_TYPES = [
  { value: "shirt", label: "Shirt" },
  { value: "pant", label: "Pant" },
  { value: "shoes", label: "Shoes" },
  { value: "sports-gear", label: "Sports Gear" },
  { value: "accessories", label: "Accessories" },
  { value: "outerwear", label: "Outerwear" },
  { value: "undergarments", label: "Undergarments" },
  { value: "other", label: "Other" },
] as const;

// Condition options
export const CONDITION_OPTIONS = [
  { value: "new", label: "New" },
  { value: "like-new", label: "Like New" },
  { value: "good", label: "Good" },
  { value: "fair", label: "Fair" },
  { value: "poor", label: "Poor" },
] as const;
