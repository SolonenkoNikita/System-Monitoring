#!/bin/bash

PROJECT_ROOT="../"
BUILD_DIR="${PROJECT_ROOT}/build"

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
  echo "Creating a directory $BUILD_DIR..."
  mkdir -p "$BUILD_DIR"
fi

cd "$BUILD_DIR" || exit

echo "Running cmake..."
cmake ..

echo "Building the project..."
make

if [ $? -eq 0 ]; then
  echo "The build has been completed successfully!"

  BINARY_PATH="Dialogue/Dialogue"
  if [ -f "$BINARY_PATH" ]; then
    echo "Launching the binary..."
    ./"$BINARY_PATH"
  else
    echo "Error: binary $BINARY_PATH not found!"
    exit 1
  fi
else
  echo "Error: Failed to build the project!"
  exit 1
fi