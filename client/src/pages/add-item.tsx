import { useState } from "react";
import { useLocation } from "wouter";
import { useForm } from "react-hook-form";
import { zodResolver } from "@hookform/resolvers/zod";
import { ArrowLeft, Save, Check, Info, Image, Images } from "lucide-react";
import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { Textarea } from "@/components/ui/textarea";
import { Select, SelectContent, SelectItem, SelectTrigger, SelectValue } from "@/components/ui/select";
import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { Form, FormControl, FormField, FormItem, FormLabel, FormMessage, FormDescription } from "@/components/ui/form";
import { useToast } from "@/hooks/use-toast";
import { useCreateItem } from "@/hooks/use-items";
import { insertItemSchema, ITEM_TYPES, CONDITION_OPTIONS, type InsertItem } from "@shared/schema";
import ImageUpload from "@/components/image-upload";
import LoadingOverlay from "@/components/loading-overlay";

export default function AddItemPage() {
  const [, setLocation] = useLocation();
  const { toast } = useToast();
  const createItemMutation = useCreateItem();
  const [coverImage, setCoverImage] = useState<string | null>(null);
  const [additionalImages, setAdditionalImages] = useState<string[]>([]);

  const form = useForm<InsertItem>({
    resolver: zodResolver(insertItemSchema),
    defaultValues: {
      name: "",
      type: "",
      condition: "new",
      description: "",
      coverImage: "",
      additionalImages: [],
    },
  });

  const onSubmit = async (data: InsertItem) => {
    try {
      // Include uploaded images in the form data
      const itemData = {
        ...data,
        coverImage: coverImage || "",
        additionalImages: additionalImages,
      };

      await createItemMutation.mutateAsync(itemData);
      
      toast({
        title: "Success!",
        description: "Item added successfully to your inventory.",
        className: "success-animation",
      });

      // Reset form and navigate back
      form.reset();
      setCoverImage(null);
      setAdditionalImages([]);
      
      setTimeout(() => {
        setLocation("/");
      }, 1000);
    } catch (error) {
      toast({
        title: "Error",
        description: error instanceof Error ? error.message : "Failed to add item. Please try again.",
        variant: "destructive",
      });
    }
  };

  const handleCancel = () => {
    if (form.formState.isDirty) {
      const confirmed = window.confirm(
        "You have unsaved changes. Are you sure you want to leave this page?"
      );
      if (!confirmed) return;
    }
    setLocation("/");
  };

  return (
    <div className="min-h-screen">
      {/* Header */}
      <header className="bg-white shadow-sm border-b border-gray-200 sticky top-0 z-40">
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
          <div className="flex justify-between items-center h-16">
            <div className="flex items-center space-x-4">
              <Button
                variant="ghost"
                size="sm"
                onClick={() => setLocation("/")}
                className="flex items-center space-x-2"
              >
                <ArrowLeft className="h-4 w-4" />
                <span>Back to Items</span>
              </Button>
            </div>
            
            <div className="flex items-center space-x-3">
              <h1 className="text-xl font-bold text-gray-900">Add New Item</h1>
            </div>
            
            <div className="w-32" /> {/* Spacer for centered title */}
          </div>
        </div>
      </header>

      {/* Main Content */}
      <main className="max-w-4xl mx-auto px-4 sm:px-6 lg:px-8 py-8">
        <div className="mb-8">
          <h2 className="text-2xl font-bold text-gray-900 mb-2">Add New Item</h2>
          <p className="text-gray-600">Fill in the details below to add a new item to your inventory.</p>
        </div>

        <Form {...form}>
          <form onSubmit={form.handleSubmit(onSubmit)} className="space-y-8">
            {/* Basic Information Section */}
            <Card>
              <CardHeader>
                <CardTitle className="flex items-center space-x-3">
                  <Info className="h-5 w-5 text-primary" />
                  <span>Basic Information</span>
                </CardTitle>
              </CardHeader>
              <CardContent className="space-y-6">
                <div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
                  {/* Item Name */}
                  <div className="lg:col-span-2">
                    <FormField
                      control={form.control}
                      name="name"
                      render={({ field }) => (
                        <FormItem>
                          <FormLabel>
                            Item Name <span className="text-red-500">*</span>
                          </FormLabel>
                          <FormControl>
                            <Input
                              placeholder="Enter item name"
                              {...field}
                              className="transition-all duration-200 focus:form-field-focused"
                            />
                          </FormControl>
                          <FormMessage />
                        </FormItem>
                      )}
                    />
                  </div>

                  {/* Item Type */}
                  <FormField
                    control={form.control}
                    name="type"
                    render={({ field }) => (
                      <FormItem>
                        <FormLabel>
                          Item Type <span className="text-red-500">*</span>
                        </FormLabel>
                        <Select onValueChange={field.onChange} defaultValue={field.value}>
                          <FormControl>
                            <SelectTrigger className="transition-all duration-200 focus:form-field-focused">
                              <SelectValue placeholder="Select item type" />
                            </SelectTrigger>
                          </FormControl>
                          <SelectContent>
                            {ITEM_TYPES.map((type) => (
                              <SelectItem key={type.value} value={type.value}>
                                {type.label}
                              </SelectItem>
                            ))}
                          </SelectContent>
                        </Select>
                        <FormMessage />
                      </FormItem>
                    )}
                  />

                  {/* Condition */}
                  <FormField
                    control={form.control}
                    name="condition"
                    render={({ field }) => (
                      <FormItem>
                        <FormLabel>Condition</FormLabel>
                        <Select onValueChange={field.onChange} defaultValue={field.value}>
                          <FormControl>
                            <SelectTrigger className="transition-all duration-200 focus:form-field-focused">
                              <SelectValue placeholder="Select condition" />
                            </SelectTrigger>
                          </FormControl>
                          <SelectContent>
                            {CONDITION_OPTIONS.map((condition) => (
                              <SelectItem key={condition.value} value={condition.value}>
                                {condition.label}
                              </SelectItem>
                            ))}
                          </SelectContent>
                        </Select>
                        <FormMessage />
                      </FormItem>
                    )}
                  />
                </div>

                {/* Item Description */}
                <FormField
                  control={form.control}
                  name="description"
                  render={({ field }) => (
                    <FormItem>
                      <FormLabel>Item Description</FormLabel>
                      <FormControl>
                        <Textarea
                          placeholder="Describe your item in detail..."
                          className="resize-none transition-all duration-200 focus:form-field-focused"
                          rows={4}
                          {...field}
                        />
                      </FormControl>
                      <FormDescription>
                        Provide details about size, color, brand, and any special features.
                      </FormDescription>
                      <FormMessage />
                    </FormItem>
                  )}
                />
              </CardContent>
            </Card>

            {/* Cover Image Section */}
            <Card>
              <CardHeader>
                <CardTitle className="flex items-center space-x-3">
                  <Image className="h-5 w-5 text-primary" />
                  <span>Cover Image</span>
                  <span className="text-red-500">*</span>
                </CardTitle>
              </CardHeader>
              <CardContent>
                <ImageUpload
                  value={coverImage}
                  onChange={setCoverImage}
                  title="Upload Cover Image"
                  description="Drag and drop your image here, or click to browse"
                  subtitle="PNG, JPG, GIF up to 10MB"
                />
              </CardContent>
            </Card>

            {/* Additional Images Section */}
            <Card>
              <CardHeader>
                <CardTitle className="flex items-center space-x-3">
                  <Images className="h-5 w-5 text-primary" />
                  <span>Additional Images</span>
                  <span className="text-sm font-normal text-gray-500 ml-2">(Optional)</span>
                </CardTitle>
              </CardHeader>
              <CardContent>
                <ImageUpload
                  value={additionalImages}
                  onChange={setAdditionalImages}
                  multiple
                  title="Add More Images"
                  description="Upload multiple images to showcase your item"
                  subtitle="Up to 5 additional images"
                />
              </CardContent>
            </Card>

            {/* Form Actions */}
            <div className="flex flex-col sm:flex-row justify-end space-y-3 sm:space-y-0 sm:space-x-4 pt-6">
              <Button
                type="button"
                variant="outline"
                onClick={handleCancel}
                className="px-6 py-3 font-medium"
              >
                Cancel
              </Button>
              <Button
                type="button"
                variant="secondary"
                className="px-6 py-3 font-medium"
                onClick={() => {
                  // TODO: Implement save as draft functionality
                  toast({
                    title: "Draft Saved",
                    description: "Your item has been saved as a draft.",
                  });
                }}
              >
                <Save className="mr-2 h-4 w-4" />
                Save as Draft
              </Button>
              <Button
                type="submit"
                className="px-6 py-3 font-medium"
                disabled={createItemMutation.isPending}
              >
                {createItemMutation.isPending ? (
                  <>
                    <div className="animate-spin rounded-full h-4 w-4 border-b-2 border-white mr-2" />
                    Adding Item...
                  </>
                ) : (
                  <>
                    <Check className="mr-2 h-4 w-4" />
                    Add Item
                  </>
                )}
              </Button>
            </div>
          </form>
        </Form>
      </main>

      {/* Loading Overlay */}
      {createItemMutation.isPending && <LoadingOverlay />}
    </div>
  );
}
