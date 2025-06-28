# Zappy

## Prerequisites

Before starting, make sure you have installed:

- **Node.js**
- **npm**

## Installation

### 1. Install dependencies

```bash
npm install
```

### 2. Environment variables configuration

Edit the `.env` file with your own values, for example:

```env
PUBLIC_URL=https://localhost:3000/Zappy
REACT_APP_GITHUB_URL=https://github.com/user/repo
PORT=3000
```

> **Note:** /Zappy must be present

## Available Scripts

### Development

```bash
# Start the development server
npm start
```

The application will be accessible at [http://localhost:3000/Zappy](http://localhost:3000/Zappy)

### Build

```bash
# Create a production build
npm run build
```

Optimized files will be generated in the `build/` folder.

## Configuration

### Environment Variables

| Variable | Description | Example |
|----------|-------------|---------|
| `PUBLIC_URL` | Public URL for assets | `https://localhost:3000/Zappy` |
| `REACT_APP_GITHUB_URL` | GitHub repository URL | `https://github.com/user/repo` |

## Troubleshooting

### Port Error

If port 3000 is already in use:
```bash
# Specify another port
PORT=3001 npm start
```