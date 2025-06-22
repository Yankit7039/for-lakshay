import { useRef } from "react";
import { Upload, X, Plus } from "lucide-react";
import { Button } from "@/components/ui/button";
import { useToast } from "@/hooks/use-toast";

interface ImageUploadProps {
  value: string | string[] | null;
  onChange: (value: string | string[] | null) => void;
  multiple?: boolean;
  title: string;
  description: string;
  subtitle: string;
}

export default function ImageUpload({
  value,
  onChange,
  multiple = false,
  title,
  description,
  subtitle,
}: ImageUploadProps) {
  const { toast } = useToast();
  const fileInputRef = useRef<HTMLInputElement>(null);

  const handleFileSelect = (e: React.ChangeEvent<HTMLInputElement>) => {
    const files = Array.from(e.target.files || []);
    
    if (files.length === 0) return;

    // Validate file types
    const validTypes = ["image/jpeg", "image/jpg", "image/png", "image/gif"];
    const invalidFiles = files.filter(file => !validTypes.includes(file.type));
    
    if (invalidFiles.length > 0) {
      toast({
        title: "Invalid File Type",
        description: "Please select only JPG, PNG, or GIF images.",
        variant: "destructive",
      });
      return;
    }

    // Validate file sizes (10MB limit)
    const maxSize = 10 * 1024 * 1024; // 10MB
    const oversizedFiles = files.filter(file => file.size > maxSize);
    
    if (oversizedFiles.length > 0) {
      toast({
        title: "File Too Large",
        description: "Please select images smaller than 10MB.",
        variant: "destructive",
      });
      return;
    }

    // Process files
    if (multiple) {
      const currentImages = Array.isArray(value) ? value : [];
      const newImages = files.slice(0, Math.max(0, 5 - currentImages.length)); // Limit to 5 total
      
      // Convert files to data URLs for preview
      const readers = newImages.map(file => {
        return new Promise<string>((resolve) => {
          const reader = new FileReader();
          reader.onload = (e) => resolve(e.target?.result as string);
          reader.readAsDataURL(file);
        });
      });

      Promise.all(readers).then(dataUrls => {
        onChange([...currentImages, ...dataUrls]);
      });
    } else {
      const file = files[0];
      const reader = new FileReader();
      reader.onload = (e) => {
        onChange(e.target?.result as string);
      };
      reader.readAsDataURL(file);
    }

    // Reset input
    if (fileInputRef.current) {
      fileInputRef.current.value = "";
    }
  };

  const handleDrop = (e: React.DragEvent) => {
    e.preventDefault();
    const files = Array.from(e.dataTransfer.files);
    
    // Simulate file input event
    const inputEvent = {
      target: { files }
    } as React.ChangeEvent<HTMLInputElement>;
    
    handleFileSelect(inputEvent);
  };

  const handleDragOver = (e: React.DragEvent) => {
    e.preventDefault();
  };

  const removeImage = (index?: number) => {
    if (multiple && Array.isArray(value)) {
      if (typeof index === 'number') {
        const newImages = value.filter((_, i) => i !== index);
        onChange(newImages.length > 0 ? newImages : null);
      }
    } else {
      onChange(null);
    }
  };

  const images = multiple ? (Array.isArray(value) ? value : []) : (value ? [value] : []);
  const hasImages = images.length > 0;

  return (
    <div className="space-y-4">
      {/* Upload Area */}
      <div
        className="image-upload-area border-2 border-dashed border-gray-300 rounded-lg p-8 text-center cursor-pointer hover:border-primary hover:bg-gray-50 transition-all duration-200"
        onClick={() => fileInputRef.current?.click()}
        onDrop={handleDrop}
        onDragOver={handleDragOver}
      >
        <div className="space-y-4">
          <div className="w-16 h-16 mx-auto bg-gray-100 rounded-full flex items-center justify-center">
            {multiple && hasImages ? (
              <Plus className="text-gray-400 h-8 w-8" />
            ) : (
              <Upload className="text-gray-400 h-8 w-8" />
            )}
          </div>
          <div>
            <h4 className="text-lg font-medium text-gray-900">{title}</h4>
            <p className="text-gray-500">{description}</p>
            <p className="text-sm text-gray-400 mt-1">{subtitle}</p>
          </div>
        </div>
        <input
          ref={fileInputRef}
          type="file"
          accept="image/*"
          multiple={multiple}
          onChange={handleFileSelect}
          className="hidden"
        />
      </div>

      {/* Image Previews */}
      {hasImages && (
        <div className={`${
          multiple 
            ? "grid grid-cols-2 sm:grid-cols-3 md:grid-cols-5 gap-4"
            : "flex justify-start"
        }`}>
          {images.map((image, index) => (
            <div key={index} className="relative inline-block">
              <img
                src={image}
                alt={`Preview ${index + 1}`}
                className={`${
                  multiple ? "w-full h-24" : "w-32 h-32"
                } object-cover rounded-lg border border-gray-200`}
              />
              <Button
                type="button"
                variant="destructive"
                size="sm"
                className="absolute -top-2 -right-2 w-6 h-6 rounded-full p-0 hover:bg-red-600"
                onClick={(e) => {
                  e.stopPropagation();
                  removeImage(multiple ? index : undefined);
                }}
              >
                <X className="h-3 w-3" />
              </Button>
            </div>
          ))}
        </div>
      )}
    </div>
  );
}
