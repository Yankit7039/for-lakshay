import { Box, Tags, TrendingUp } from "lucide-react";
import { Card, CardContent } from "@/components/ui/card";
import { Skeleton } from "@/components/ui/skeleton";

interface StatsCardsProps {
  stats?: {
    totalItems: number;
    categories: number;
    recentAdditions: number;
  };
}

export default function StatsCards({ stats }: StatsCardsProps) {
  const statsData = [
    {
      title: "Total Items",
      value: stats?.totalItems ?? 0,
      icon: Box,
      color: "bg-primary-50 text-primary-600",
    },
    {
      title: "Categories", 
      value: stats?.categories ?? 0,
      icon: Tags,
      color: "bg-pink-50 text-pink-600",
    },
    {
      title: "Recent Additions",
      value: stats?.recentAdditions ?? 0,
      icon: TrendingUp,
      color: "bg-green-50 text-green-600",
    },
  ];

  return (
    <div className="grid grid-cols-1 md:grid-cols-3 gap-6 mb-8">
      {statsData.map((stat, index) => (
        <Card key={index} className="hover:shadow-md transition-shadow">
          <CardContent className="p-6">
            <div className="flex items-center justify-between">
              <div>
                <p className="text-sm font-medium text-gray-600">{stat.title}</p>
                {stats ? (
                  <p className="text-2xl font-bold text-gray-900">{stat.value}</p>
                ) : (
                  <Skeleton className="h-8 w-12 mt-1" />
                )}
              </div>
              <div className={`p-3 rounded-lg ${stat.color}`}>
                <stat.icon className="h-5 w-5" />
              </div>
            </div>
          </CardContent>
        </Card>
      ))}
    </div>
  );
}
