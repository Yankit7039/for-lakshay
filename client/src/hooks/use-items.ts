import { useQuery, useMutation, useQueryClient } from "@tanstack/react-query";
import { apiRequest } from "@/lib/queryClient";
import type { Item, InsertItem } from "@shared/schema";

export function useItems(search?: string, type?: string) {
  const queryKey = ["/api/items"];
  
  if (search) queryKey.push(`search=${encodeURIComponent(search)}`);
  if (type) queryKey.push(`type=${encodeURIComponent(type)}`);
  
  const finalUrl = queryKey.length > 1 
    ? `${queryKey[0]}?${queryKey.slice(1).join('&')}`
    : queryKey[0];

  return useQuery({
    queryKey: [finalUrl],
    queryFn: async () => {
      const response = await fetch(finalUrl);
      if (!response.ok) {
        throw new Error(`Failed to fetch items: ${response.statusText}`);
      }
      return response.json() as Promise<Item[]>;
    },
  });
}

export function useItem(id: number) {
  return useQuery({
    queryKey: ["/api/items", id],
    queryFn: async () => {
      const response = await fetch(`/api/items/${id}`);
      if (!response.ok) {
        throw new Error(`Failed to fetch item: ${response.statusText}`);
      }
      return response.json() as Promise<Item>;
    },
  });
}

export function useCreateItem() {
  const queryClient = useQueryClient();
  
  return useMutation({
    mutationFn: async (item: InsertItem) => {
      const response = await apiRequest("POST", "/api/items", item);
      return response.json() as Promise<Item>;
    },
    onSuccess: () => {
      queryClient.invalidateQueries({ queryKey: ["/api/items"] });
      queryClient.invalidateQueries({ queryKey: ["/api/stats"] });
    },
  });
}

export function useUpdateItem() {
  const queryClient = useQueryClient();
  
  return useMutation({
    mutationFn: async ({ id, item }: { id: number; item: Partial<InsertItem> }) => {
      const response = await apiRequest("PUT", `/api/items/${id}`, item);
      return response.json() as Promise<Item>;
    },
    onSuccess: (_, { id }) => {
      queryClient.invalidateQueries({ queryKey: ["/api/items"] });
      queryClient.invalidateQueries({ queryKey: ["/api/items", id] });
      queryClient.invalidateQueries({ queryKey: ["/api/stats"] });
    },
  });
}

export function useDeleteItem() {
  const queryClient = useQueryClient();
  
  return useMutation({
    mutationFn: async (id: number) => {
      await apiRequest("DELETE", `/api/items/${id}`);
    },
    onSuccess: () => {
      queryClient.invalidateQueries({ queryKey: ["/api/items"] });
      queryClient.invalidateQueries({ queryKey: ["/api/stats"] });
    },
  });
}

export function useStats() {
  return useQuery({
    queryKey: ["/api/stats"],
    queryFn: async () => {
      const response = await fetch("/api/stats");
      if (!response.ok) {
        throw new Error(`Failed to fetch stats: ${response.statusText}`);
      }
      return response.json() as Promise<{
        totalItems: number;
        categories: number;
        recentAdditions: number;
      }>;
    },
  });
}
