#!/bin/bash

PROJECT_ROOT="../"

BUILD_DIR="${PROJECT_ROOT}/build"

if [ ! -d "$BUILD_DIR" ]; then
  echo "Creating a directory $BUILD_DIR..."
  mkdir -p "$BUILD_DIR"
fi

cd "$BUILD_DIR" || exit

echo "Running cmake..."
cmake ..


echo "Building a project..."
make

if [ $? -eq 0 ]; then
  echo "The build has been completed successfully!"

  BINARY_PATH="Dialogue/Dialogue"

  if [ -f "$BINARY_PATH" ]; then
    echo "Launching the binary..."
    ./"$BINARY_PATH"
  else
    echo "Error: binary $BINARY_PATH hasn't found!"
    exit 1
  fi
else
  echo "Error when building the project!"
  exit 1
fi