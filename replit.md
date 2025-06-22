# Inventory Management Application

## Overview

This is a full-stack inventory management application built with React, Express, and PostgreSQL. The application allows users to add, view, search, and manage inventory items with features like image uploads, categorization, and condition tracking. It uses a modern tech stack with TypeScript throughout and implements a clean, responsive UI using shadcn/ui components.

## System Architecture

### Frontend Architecture
- **Framework**: React 18 with TypeScript
- **Build Tool**: Vite for fast development and optimized builds
- **Routing**: Wouter for lightweight client-side routing
- **State Management**: TanStack Query (React Query) for server state management
- **UI Framework**: shadcn/ui components built on Radix UI primitives
- **Styling**: Tailwind CSS with custom design tokens and Inter font
- **Form Handling**: React Hook Form with Zod validation

### Backend Architecture
- **Runtime**: Node.js with Express.js framework
- **Language**: TypeScript with ES modules
- **Database**: PostgreSQL with Drizzle ORM
- **Database Provider**: Neon serverless PostgreSQL
- **Session Management**: Express sessions with PostgreSQL store
- **Development**: TSX for TypeScript execution in development

### Database Schema
The application uses two main entities:
- **Users**: Basic user management with username/password authentication
- **Items**: Inventory items with comprehensive metadata including name, type, condition, description, images, and timestamps

## Key Components

### Data Management
- **Drizzle ORM**: Type-safe database operations with schema validation
- **Zod Schemas**: Runtime validation for both client and server
- **Memory Storage**: Fallback storage implementation with sample data for development

### User Interface
- **Responsive Design**: Mobile-first approach with adaptive layouts
- **Component Library**: Comprehensive UI components from shadcn/ui
- **Image Handling**: Upload and display system for item images
- **Search & Filter**: Real-time search with category and condition filtering
- **View Modes**: Grid and list view options for item display

### Core Features
- **Item Management**: CRUD operations for inventory items
- **Image Upload**: Multiple image support with cover image selection
- **Search Functionality**: Text-based search across item names and descriptions
- **Category Filtering**: Filter items by type (shirt, pant, shoes)
- **Statistics Dashboard**: Overview of total items, categories, and recent additions

## Data Flow

1. **Client Requests**: React components use TanStack Query hooks for data fetching
2. **API Layer**: Express routes handle HTTP requests with validation
3. **Database Operations**: Drizzle ORM manages PostgreSQL interactions
4. **Response Handling**: Standardized JSON responses with error handling
5. **State Updates**: Query cache automatically updates UI components

The application follows a typical client-server pattern where the React frontend communicates with the Express backend through RESTful API endpoints. All data validation occurs on both client and server sides using shared Zod schemas.

## External Dependencies

### Frontend Dependencies
- **UI Components**: Radix UI primitives for accessible component building
- **Form Management**: React Hook Form with Zod resolvers
- **Date Handling**: date-fns for date formatting and manipulation
- **Styling**: Tailwind CSS with class-variance-authority for component variants

### Backend Dependencies
- **Database**: @neondatabase/serverless for PostgreSQL connectivity
- **ORM**: Drizzle ORM with PostgreSQL dialect
- **Session Storage**: connect-pg-simple for PostgreSQL session store
- **Development**: Various build tools and TypeScript utilities

### Development Tools
- **Build System**: Vite with React plugin and Replit-specific plugins
- **Type Checking**: TypeScript with strict configuration
- **Code Quality**: ESLint integration (configured via Vite)

## Deployment Strategy

### Development Environment
- **Platform**: Replit with Node.js 20 and PostgreSQL 16 modules
- **Hot Reload**: Vite development server with HMR support
- **Database**: Provisioned PostgreSQL instance via environment variables

### Production Build
- **Frontend**: Vite builds optimized static assets to `dist/public`
- **Backend**: esbuild bundles server code to `dist/index.js`
- **Deployment**: Replit autoscale deployment with build and run commands
- **Port Configuration**: Server runs on port 5000, external port 80

### Database Management
- **Migrations**: Drizzle Kit handles schema migrations
- **Connection**: Database URL provided via environment variables
- **Schema**: Located in `shared/schema.ts` for type sharing between client and server

## Changelog

```
Changelog:
- June 22, 2025. Initial setup
```

## User Preferences

```
Preferred communication style: Simple, everyday language.
```