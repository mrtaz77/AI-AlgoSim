#!/bin/bash

# Check if two arguments are provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <input_dir> <output_dir>"
    exit 1
fi

# Input and output directories, enclose them in quotes to handle spaces
input_dir="$1"
output_dir="$2"

# Create the output directory if it doesn't exist
mkdir -p "$output_dir"

# Find and copy .cpp, .hpp, .c, .h files and Makefile
find "$input_dir" \( -name "*.cpp" -o -name "*.hpp" -o -name "*.c" -o -name "*.h" -o -name "Makefile" \) \
    -print0 | while IFS= read -r -d '' file; do
    # Create the directory structure in the output directory
    target_dir="$output_dir/$(dirname "${file#$input_dir}")"
    mkdir -p "$target_dir"
    
    # Copy the file to the corresponding directory in the output
    cp "$file" "$target_dir"
done

echo "Files copied to $output_dir"
