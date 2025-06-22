import { useState, useMemo } from "react";
import { Link, useLocation } from "wouter";
import { Search, Filter, Grid, List, Plus, Box, Tags, TrendingUp } from "lucide-react";
import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { Select, SelectContent, SelectItem, SelectTrigger, SelectValue } from "@/components/ui/select";
import { Card, CardContent } from "@/components/ui/card";
import { Skeleton } from "@/components/ui/skeleton";
import { useItems, useStats } from "@/hooks/use-items";
import { ITEM_TYPES } from "@shared/schema";
import { debounce } from "@/lib/utils";
import ItemCard from "@/components/item-card";
import ItemDetailModal from "@/components/item-detail-modal";
import StatsCards from "@/components/stats-cards";
import LoadingOverlay from "@/components/loading-overlay";

export default function ViewItemsPage() {
  const [, setLocation] = useLocation();
  const [searchQuery, setSearchQuery] = useState("");
  const [selectedCategory, setSelectedCategory] = useState("all");
  const [sortBy, setSortBy] = useState("newest");
  const [viewMode, setViewMode] = useState<"grid" | "list">("grid");
  const [selectedItemId, setSelectedItemId] = useState<number | null>(null);

  // Debounced search to avoid too many API calls
  const debouncedSearch = useMemo(
    () => debounce((query: string) => setSearchQuery(query), 300),
    []
  );

  const { data: items = [], isLoading, error } = useItems(
    searchQuery || undefined,
    selectedCategory && selectedCategory !== "all" ? selectedCategory : undefined
  );

  const { data: stats } = useStats();

  // Sort items based on selected option
  const sortedItems = useMemo(() => {
    if (!items) return [];
    
    const itemsCopy = [...items];
    
    switch (sortBy) {
      case "oldest":
        return itemsCopy.sort((a, b) => 
          new Date(a.dateAdded).getTime() - new Date(b.dateAdded).getTime()
        );
      case "name":
        return itemsCopy.sort((a, b) => a.name.localeCompare(b.name));
      case "name-desc":
        return itemsCopy.sort((a, b) => b.name.localeCompare(a.name));
      case "newest":
      default:
        return itemsCopy.sort((a, b) => 
          new Date(b.dateAdded).getTime() - new Date(a.dateAdded).getTime()
        );
    }
  }, [items, sortBy]);

  const handleSearch = (value: string) => {
    debouncedSearch(value);
  };

  const handleItemClick = (itemId: number) => {
    setSelectedItemId(itemId);
  };

  const handleCloseModal = () => {
    setSelectedItemId(null);
  };

  if (error) {
    return (
      <div className="min-h-screen flex items-center justify-center">
        <Card className="w-full max-w-md mx-4">
          <CardContent className="pt-6 text-center">
            <div className="w-16 h-16 mx-auto bg-red-100 rounded-full flex items-center justify-center mb-4">
              <i className="fas fa-exclamation-triangle text-red-600 text-2xl"></i>
            </div>
            <h3 className="text-lg font-semibold text-gray-900 mb-2">Failed to Load Items</h3>
            <p className="text-gray-600 mb-4">
              {error instanceof Error ? error.message : "An unexpected error occurred"}
            </p>
            <Button onClick={() => window.location.reload()}>
              Try Again
            </Button>
          </CardContent>
        </Card>
      </div>
    );
  }

  return (
    <div className="min-h-screen">
      {/* Header */}
      <header className="bg-white shadow-sm border-b border-gray-200 sticky top-0 z-40">
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
          <div className="flex justify-between items-center h-16">
            <div className="flex items-center space-x-4">
              <div className="flex items-center space-x-3">
                <div className="w-8 h-8 bg-gradient-to-r from-[hsl(249,91%,66%)] to-[hsl(328,85%,70%)] rounded-lg flex items-center justify-center">
                  <Box className="text-white text-sm" />
                </div>
                <h1 className="text-xl font-bold text-gray-900">ItemManager Pro</h1>
              </div>
            </div>
            
            <nav className="hidden md:flex space-x-8">
              <Button variant="default" className="px-3 py-2 text-sm font-medium">
                <Grid className="mr-2 h-4 w-4" />
                View Items
              </Button>
              <Button 
                variant="outline" 
                className="px-3 py-2 text-sm font-medium"
                onClick={() => setLocation("/add-item")}
              >
                <Plus className="mr-2 h-4 w-4" />
                Add Item
              </Button>
            </nav>
            
            <div className="flex items-center space-x-4">
              <div className="relative">
                <Input
                  type="text"
                  placeholder="Search items..."
                  className="pl-10 pr-4 py-2 w-64 transition-all duration-200"
                  onChange={(e) => handleSearch(e.target.value)}
                />
                <Search className="absolute left-3 top-1/2 transform -translate-y-1/2 text-gray-400 h-4 w-4" />
              </div>
            </div>
          </div>
        </div>
      </header>

      {/* Main Content */}
      <main className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-8">
        {/* Stats Cards */}
        <StatsCards stats={stats} />

        {/* Filters and Controls */}
        <Card className="mb-8">
          <CardContent className="p-6">
            <div className="flex flex-col lg:flex-row lg:items-center lg:justify-between space-y-4 lg:space-y-0">
              <div className="flex flex-col sm:flex-row space-y-4 sm:space-y-0 sm:space-x-4">
                <Select value={selectedCategory} onValueChange={setSelectedCategory}>
                  <SelectTrigger className="w-full sm:w-48">
                    <SelectValue placeholder="All Categories" />
                  </SelectTrigger>
                  <SelectContent>
                    <SelectItem value="all">All Categories</SelectItem>
                    {ITEM_TYPES.map(type => (
                      <SelectItem key={type.value} value={type.value}>
                        {type.label}
                      </SelectItem>
                    ))}
                  </SelectContent>
                </Select>
                
                <Select value={sortBy} onValueChange={setSortBy}>
                  <SelectTrigger className="w-full sm:w-48">
                    <SelectValue placeholder="Sort by" />
                  </SelectTrigger>
                  <SelectContent>
                    <SelectItem value="newest">Newest First</SelectItem>
                    <SelectItem value="oldest">Oldest First</SelectItem>
                    <SelectItem value="name">Name A-Z</SelectItem>
                    <SelectItem value="name-desc">Name Z-A</SelectItem>
                  </SelectContent>
                </Select>
              </div>
              
              <div className="flex items-center space-x-4">
                <div className="flex items-center space-x-2">
                  <Button
                    variant={viewMode === "grid" ? "default" : "outline"}
                    size="sm"
                    onClick={() => setViewMode("grid")}
                  >
                    <Grid className="h-4 w-4" />
                  </Button>
                  <Button
                    variant={viewMode === "list" ? "default" : "outline"}
                    size="sm"
                    onClick={() => setViewMode("list")}
                  >
                    <List className="h-4 w-4" />
                  </Button>
                </div>
                <span className="text-sm text-gray-500">
                  {sortedItems.length} items
                </span>
              </div>
            </div>
          </CardContent>
        </Card>

        {/* Items Grid/List */}
        {isLoading ? (
          <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-6">
            {Array.from({ length: 8 }).map((_, i) => (
              <Card key={i} className="overflow-hidden">
                <Skeleton className="aspect-square w-full" />
                <CardContent className="p-4">
                  <Skeleton className="h-4 w-3/4 mb-2" />
                  <Skeleton className="h-3 w-full mb-1" />
                  <Skeleton className="h-3 w-2/3" />
                </CardContent>
              </Card>
            ))}
          </div>
        ) : sortedItems.length === 0 ? (
          <div className="text-center py-16">
            <div className="w-24 h-24 mx-auto bg-gray-100 rounded-full flex items-center justify-center mb-6">
              <Box className="text-gray-400 h-12 w-12" />
            </div>
            <h3 className="text-lg font-medium text-gray-900 mb-2">No items found</h3>
            <p className="text-gray-500 mb-6">
              {searchQuery || selectedCategory 
                ? "Try adjusting your search or filters"
                : "Get started by adding your first item to the inventory"
              }
            </p>
            <Button onClick={() => setLocation("/add-item")}>
              <Plus className="mr-2 h-4 w-4" />
              Add Your First Item
            </Button>
          </div>
        ) : (
          <div className={`grid gap-6 ${
            viewMode === "grid" 
              ? "grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4" 
              : "grid-cols-1"
          }`}>
            {sortedItems.map((item) => (
              <ItemCard
                key={item.id}
                item={item}
                viewMode={viewMode}
                onClick={() => handleItemClick(item.id)}
              />
            ))}
          </div>
        )}
      </main>

      {/* Floating Add Button (Mobile) */}
      <Button
        className="fixed bottom-6 right-6 w-14 h-14 rounded-full shadow-lg md:hidden hover:scale-110 transition-transform"
        onClick={() => setLocation("/add-item")}
      >
        <Plus className="h-6 w-6" />
      </Button>

      {/* Item Detail Modal */}
      {selectedItemId && (
        <ItemDetailModal
          itemId={selectedItemId}
          onClose={handleCloseModal}
        />
      )}
    </div>
  );
}
