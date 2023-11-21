#!/bin/bash
clang++ -o ../herramientas/lectura ../herramientas/lectura.cpp
echo "Compilado lectura_traza.cpp"
# Check if a folder path is provided as a command-line argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 /path/to/folder"
    exit 1
fi

folder_path="$1"

# Check if the provided path is a directory
if [ ! -d "$folder_path" ]; then
    echo "Error: $folder_path is not a directory."
    exit 1
fi

# Change to the specified directory
cd "$folder_path" || exit

# Iterate through all .fld files in the specified folder
for file in *.fld; do
    # Check if the file is a regular file
    if [ -f "$file" ]; then
        # Define the output file name based on the input file
        output_file="${file%.fld}_output.txt"
        echo "Processing file: $file" > "$output_file"
        ../herramientas/lectura "$file" >> "$output_file"
    fi
done
