import { Card, CardContent } from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { Badge } from "@/components/ui/badge";
import { ArrowRight, Trash2 } from "lucide-react";
import { formatDate, formatImageUrl, capitalizeFirst } from "@/lib/utils";
import { useDeleteItem } from "@/hooks/use-items";
import { useToast } from "@/hooks/use-toast";
import type { Item } from "@shared/schema";

interface ItemCardProps {
  item: Item;
  viewMode: "grid" | "list";
  onClick: () => void;
}

export default function ItemCard({ item, viewMode, onClick }: ItemCardProps) {
  const imageUrl = formatImageUrl(item.coverImage);
  const deleteItemMutation = useDeleteItem();
  const { toast } = useToast();

  const handleDelete = async (e: React.MouseEvent) => {
    e.stopPropagation(); // Prevent opening the modal
    
    const confirmed = window.confirm(
      `Are you sure you want to delete "${item.name}"? This action cannot be undone.`
    );
    
    if (!confirmed) return;
    
    try {
      await deleteItemMutation.mutateAsync(item.id);
      toast({
        title: "Item Deleted",
        description: "The item has been successfully deleted from your inventory.",
      });
    } catch (error) {
      toast({
        title: "Error",
        description: error instanceof Error ? error.message : "Failed to delete item. Please try again.",
        variant: "destructive",
      });
    }
  };

  if (viewMode === "list") {
    return (
      <Card className="item-card cursor-pointer" onClick={onClick}>
        <CardContent className="p-4">
          <div className="flex items-center space-x-4">
            <div className="w-20 h-20 flex-shrink-0 rounded-lg overflow-hidden bg-gray-100">
              {imageUrl ? (
                <img
                  src={imageUrl}
                  alt={item.name}
                  className="w-full h-full object-cover"
                />
              ) : (
                <div className="w-full h-full bg-gray-200 flex items-center justify-center">
                  <span className="text-gray-400 text-xs">No Image</span>
                </div>
              )}
            </div>
            
            <div className="flex-1 min-w-0">
              <div className="flex items-center space-x-2 mb-1">
                <h3 className="font-medium text-gray-900 truncate">{item.name}</h3>
                <Badge variant="secondary" className="text-xs">
                  {capitalizeFirst(item.type.replace("-", " "))}
                </Badge>
                <Badge variant="outline" className="text-xs">
                  {capitalizeFirst(item.condition)}
                </Badge>
              </div>
              
              <p className="text-sm text-gray-500 line-clamp-2 mb-2">
                {item.description || "No description available"}
              </p>
              
              <div className="flex items-center justify-between">
                <span className="text-xs text-gray-400">
                  {formatDate(item.dateAdded)}
                </span>
                <div className="flex items-center space-x-2">
                  <Button variant="ghost" size="sm" className="text-primary hover:text-primary-700">
                    Enquire <ArrowRight className="ml-1 h-3 w-3" />
                  </Button>
                  <Button
                    variant="ghost"
                    size="sm"
                    className="text-red-600 hover:text-red-700 hover:bg-red-50"
                    onClick={handleDelete}
                    disabled={deleteItemMutation.isPending}
                  >
                    <Trash2 className="h-3 w-3" />
                  </Button>
                </div>
              </div>
            </div>
          </div>
        </CardContent>
      </Card>
    );
  }

  return (
    <Card className="item-card cursor-pointer overflow-hidden" onClick={onClick}>
      <div className="aspect-square relative overflow-hidden">
        {imageUrl ? (
          <img
            src={imageUrl}
            alt={item.name}
            className="w-full h-full object-cover transition-transform duration-300 group-hover:scale-110"
          />
        ) : (
          <div className="w-full h-full bg-gray-200 flex items-center justify-center">
            <span className="text-gray-400">No Image</span>
          </div>
        )}
        <div className="absolute top-3 right-3">
          <Badge variant="secondary" className="bg-white bg-opacity-90 text-xs">
            {capitalizeFirst(item.type.replace("-", " "))}
          </Badge>
        </div>
        <Button
          variant="ghost"
          size="sm"
          className="absolute top-3 left-3 w-8 h-8 rounded-full bg-white bg-opacity-90 hover:bg-opacity-100 text-red-600 hover:text-red-700 hover:bg-red-50"
          onClick={handleDelete}
          disabled={deleteItemMutation.isPending}
        >
          <Trash2 className="h-3 w-3" />
        </Button>
      </div>
      
      <CardContent className="p-4">
        <h3 className="font-medium text-gray-900 mb-1 truncate">{item.name}</h3>
        <p className="text-sm text-gray-500 line-clamp-2 mb-3">
          {item.description || "No description available"}
        </p>
        
        <div className="flex items-center justify-between">
          <span className="text-xs text-gray-400">
            {formatDate(item.dateAdded)}
          </span>
          <div className="flex items-center space-x-2">
            <Button variant="ghost" size="sm" className="text-primary hover:text-primary-700">
              Enquire <ArrowRight className="ml-1 h-3 w-3" />
            </Button>
            {/* <Button
              variant="ghost"
              size="sm"
              className="text-red-600 hover:text-red-700 hover:bg-red-50"
              onClick={handleDelete}
              disabled={deleteItemMutation.isPending}
            >
              <Trash2 className="h-3 w-3" />
            </Button> */}
          </div>
        </div>
      </CardContent>
    </Card>
  );
}
