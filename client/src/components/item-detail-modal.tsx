import { useState, useEffect } from "react";
import { X, ChevronLeft, ChevronRight, Mail, Share2, Trash2 } from "lucide-react";
import { Button } from "@/components/ui/button";
import { Badge } from "@/components/ui/badge";
import { Card, CardContent } from "@/components/ui/card";
import { Skeleton } from "@/components/ui/skeleton";
import { useToast } from "@/hooks/use-toast";
import { useItem, useDeleteItem } from "@/hooks/use-items";
import { formatDate, formatImageUrl, formatThumbnailUrl, capitalizeFirst } from "@/lib/utils";

interface ItemDetailModalProps {
  itemId: number;
  onClose: () => void;
}

export default function ItemDetailModal({ itemId, onClose }: ItemDetailModalProps) {
  const { toast } = useToast();
  const { data: item, isLoading, error } = useItem(itemId);
  const deleteItemMutation = useDeleteItem();
  const [currentImageIndex, setCurrentImageIndex] = useState(0);

  // Get all images (cover + additional)
  const allImages = item ? [
    item.coverImage,
    ...(item.additionalImages || [])
  ].filter(Boolean) : [];

  const currentImage = allImages[currentImageIndex];

  // Handle keyboard navigation
  useEffect(() => {
    const handleKeyDown = (e: KeyboardEvent) => {
      if (e.key === "Escape") {
        onClose();
      } else if (e.key === "ArrowLeft") {
        previousImage();
      } else if (e.key === "ArrowRight") {
        nextImage();
      }
    };

    document.addEventListener("keydown", handleKeyDown);
    return () => document.removeEventListener("keydown", handleKeyDown);
  }, [onClose]);

  // Prevent body scroll when modal is open
  useEffect(() => {
    document.body.style.overflow = "hidden";
    return () => {
      document.body.style.overflow = "auto";
    };
  }, []);

  const nextImage = () => {
    if (allImages.length > 1) {
      setCurrentImageIndex((prev) => (prev + 1) % allImages.length);
    }
  };

  const previousImage = () => {
    if (allImages.length > 1) {
      setCurrentImageIndex((prev) => (prev - 1 + allImages.length) % allImages.length);
    }
  };

  const handleEnquire = () => {
    toast({
      title: "Enquiry Sent!",
      description: "Your enquiry has been sent successfully. We'll get back to you soon.",
    });
  };

  const handleDelete = async () => {
    if (!item) return;
    
    const confirmed = window.confirm(
      `Are you sure you want to delete "${item.name}"? This action cannot be undone.`
    );
    
    if (!confirmed) return;
    
    try {
      await deleteItemMutation.mutateAsync(itemId);
      toast({
        title: "Item Deleted",
        description: "The item has been successfully deleted from your inventory.",
      });
      onClose();
    } catch (error) {
      toast({
        title: "Error",
        description: error instanceof Error ? error.message : "Failed to delete item. Please try again.",
        variant: "destructive",
      });
    }
  };

  const handleShare = async () => {
    try {
      if (navigator.share && item) {
        await navigator.share({
          title: item.name,
          text: item.description || `Check out this ${item.type}: ${item.name}`,
          url: window.location.href,
        });
      } else {
        // Fallback: copy to clipboard
        await navigator.clipboard.writeText(window.location.href);
        toast({
          title: "Link Copied!",
          description: "Item link has been copied to your clipboard.",
        });
      }
    } catch (error) {
      toast({
        title: "Share Failed",
        description: "Could not share this item. Please try again.",
        variant: "destructive",
      });
    }
  };

  if (error) {
    return (
      <div className="fixed inset-0 z-50 modal-backdrop">
        <div className="fixed inset-0 overflow-y-auto">
          <div className="flex min-h-full items-center justify-center p-4">
            <Card className="relative bg-white rounded-2xl shadow-2xl max-w-md w-full animate-slide-up">
              <CardContent className="pt-6 text-center">
                <div className="w-16 h-16 mx-auto bg-red-100 rounded-full flex items-center justify-center mb-4">
                  <X className="text-red-600 h-8 w-8" />
                </div>
                <h3 className="text-lg font-semibold text-gray-900 mb-2">Failed to Load Item</h3>
                <p className="text-gray-600 mb-4">
                  {error instanceof Error ? error.message : "An unexpected error occurred"}
                </p>
                <Button onClick={onClose}>Close</Button>
              </CardContent>
            </Card>
          </div>
        </div>
      </div>
    );
  }

  return (
    <div className="fixed inset-0 z-50 modal-backdrop" onClick={onClose}>
      <div className="fixed inset-0 overflow-y-auto">
        <div className="flex min-h-full items-center justify-center p-4">
          <div
            className="relative bg-white rounded-2xl shadow-2xl max-w-4xl w-full max-h-[90vh] overflow-hidden animate-slide-up"
            onClick={(e) => e.stopPropagation()}
          >
            {/* Modal Header */}
            <div className="flex items-center justify-between p-6 border-b border-gray-200">
              <h3 className="text-xl font-semibold text-gray-900">
                {isLoading ? "Loading..." : item?.name || "Item Details"}
              </h3>
              <Button variant="ghost" size="sm" onClick={onClose}>
                <X className="h-4 w-4" />
              </Button>
            </div>

            {/* Modal Content */}
            <div className="p-6 overflow-y-auto max-h-[calc(90vh-140px)]">
              {isLoading ? (
                <div className="grid grid-cols-1 lg:grid-cols-2 gap-8">
                  <div className="space-y-4">
                    <Skeleton className="aspect-square w-full rounded-xl" />
                    <div className="flex space-x-3">
                      {Array.from({ length: 3 }).map((_, i) => (
                        <Skeleton key={i} className="w-16 h-16 rounded-lg" />
                      ))}
                    </div>
                  </div>
                  <div className="space-y-6">
                    <Skeleton className="h-8 w-3/4" />
                    <div className="flex space-x-2">
                      <Skeleton className="h-6 w-20" />
                      <Skeleton className="h-6 w-16" />
                    </div>
                    <div className="space-y-2">
                      <Skeleton className="h-4 w-full" />
                      <Skeleton className="h-4 w-full" />
                      <Skeleton className="h-4 w-2/3" />
                    </div>
                  </div>
                </div>
              ) : item ? (
                <div className="grid grid-cols-1 lg:grid-cols-2 gap-8">
                  {/* Image Carousel */}
                  <div className="space-y-4">
                    <div className="relative aspect-square bg-gray-100 rounded-xl overflow-hidden">
                      {currentImage ? (
                        <img
                          src={formatImageUrl(currentImage)}
                          alt={item.name}
                          className="w-full h-full object-cover"
                        />
                      ) : (
                        <div className="w-full h-full bg-gray-200 flex items-center justify-center">
                          <span className="text-gray-400">No Image Available</span>
                        </div>
                      )}

                      {/* Carousel Navigation */}
                      {allImages.length > 1 && (
                        <>
                          <Button
                            variant="secondary"
                            size="sm"
                            className="absolute left-3 top-1/2 transform -translate-y-1/2 w-10 h-10 rounded-full bg-white bg-opacity-90 hover:bg-opacity-100"
                            onClick={previousImage}
                          >
                            <ChevronLeft className="h-4 w-4" />
                          </Button>
                          <Button
                            variant="secondary"
                            size="sm"
                            className="absolute right-3 top-1/2 transform -translate-y-1/2 w-10 h-10 rounded-full bg-white bg-opacity-90 hover:bg-opacity-100"
                            onClick={nextImage}
                          >
                            <ChevronRight className="h-4 w-4" />
                          </Button>

                          {/* Image Counter */}
                          <div className="absolute bottom-3 right-3 px-3 py-1 bg-black bg-opacity-60 text-white text-sm rounded-full">
                            {currentImageIndex + 1} / {allImages.length}
                          </div>
                        </>
                      )}
                    </div>

                    {/* Thumbnail Strip */}
                    {allImages.length > 1 && (
                      <div className="flex space-x-3 overflow-x-auto pb-2">
                        {allImages.map((image, index) => (
                          <button
                            key={index}
                            className={`flex-shrink-0 w-16 h-16 rounded-lg overflow-hidden border-2 transition-all ${
                              index === currentImageIndex
                                ? "border-primary opacity-100"
                                : "border-gray-200 opacity-60 hover:opacity-100"
                            }`}
                            onClick={() => setCurrentImageIndex(index)}
                          >
                            <img
                              src={formatThumbnailUrl(image)}
                              alt={`${item.name} ${index + 1}`}
                              className="w-full h-full object-cover"
                            />
                          </button>
                        ))}
                      </div>
                    )}
                  </div>

                  {/* Item Details */}
                  <div className="space-y-6">
                    <div>
                      <h2 className="text-2xl font-bold text-gray-900 mb-2">{item.name}</h2>
                      <div className="flex items-center space-x-4 mb-4">
                        <Badge className="bg-primary-100 text-primary-800 hover:bg-primary-100">
                          {capitalizeFirst(item.type.replace("-", " "))}
                        </Badge>
                        <Badge variant="outline" className="text-green-800 border-green-200">
                          {capitalizeFirst(item.condition)}
                        </Badge>
                      </div>
                    </div>

                    {item.description && (
                      <div>
                        <h3 className="text-lg font-semibold text-gray-900 mb-3">Description</h3>
                        <p className="text-gray-600 leading-relaxed">{item.description}</p>
                      </div>
                    )}

                    <div>
                      <h3 className="text-lg font-semibold text-gray-900 mb-3">Details</h3>
                      <dl className="grid grid-cols-1 sm:grid-cols-2 gap-3">
                        <div>
                          <dt className="text-sm font-medium text-gray-500">Added</dt>
                          <dd className="text-sm text-gray-900">{formatDate(item.dateAdded)}</dd>
                        </div>
                        <div>
                          <dt className="text-sm font-medium text-gray-500">Condition</dt>
                          <dd className="text-sm text-gray-900">{capitalizeFirst(item.condition)}</dd>
                        </div>
                        <div>
                          <dt className="text-sm font-medium text-gray-500">Category</dt>
                          <dd className="text-sm text-gray-900">
                            {capitalizeFirst(item.type.replace("-", " "))}
                          </dd>
                        </div>
                        <div>
                          <dt className="text-sm font-medium text-gray-500">ID</dt>
                          <dd className="text-sm text-gray-900 font-mono">#{item.id.toString().padStart(3, '0')}</dd>
                        </div>
                      </dl>
                    </div>

                    {/* Action Buttons */}
                    <div className="flex flex-col sm:flex-row space-y-3 sm:space-y-0 sm:space-x-4 pt-6 border-t border-gray-200">
                      <Button
                        className="flex-1 bg-primary-600 hover:bg-primary-700 transition-all duration-200 transform hover:scale-[1.02]"
                        onClick={handleEnquire}
                      >
                        <Mail className="mr-2 h-4 w-4" />
                        Send Enquiry
                      </Button>
                      <Button
                        variant="outline"
                        className="flex-1 transition-colors"
                        onClick={handleShare}
                      >
                        <Share2 className="mr-2 h-4 w-4" />
                        Share Item
                      </Button>
                      {/* <Button
                        variant="destructive"
                        className="flex-1 transition-colors"
                        onClick={handleDelete}
                        disabled={deleteItemMutation.isPending}
                      >
                        <Trash2 className="mr-2 h-4 w-4" />
                        {deleteItemMutation.isPending ? "Deleting..." : "Delete Item"}
                      </Button> */}
                    </div>
                  </div>
                </div>
              ) : null}
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}
