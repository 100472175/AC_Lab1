#!/bin/bash

# Compile the lectura_traza program
clang++ -o lectura_traza ../../herramientas/lectura_traza.cpp

# Function to process a single file
process_file() {
    input_file=$1
    output_file=$2

    ./lectura_traza "$input_file" > "$output_file"

    echo "Processed: $input_file -> $output_file"
}

# Export the function so it can be used by parallel
export -f process_file

# Array of file prefixes
files=("acctransf-base" "boundint-base" "densinc-base" "denstransf-base" "initacc-base" "motion-base" "partcol-base" "repos-base")

# Loop through the file prefixes and execute in parallel
for file_prefix in "${files[@]}"
do
    # Use parallel to process files concurrently
    parallel --jobs 5 process_file ::: "../small/${file_prefix}"-{1..5}.trz ::: "${file_prefix}"-{1..5}.txt
done
rm lectura_traza
echo "All files processed in parallel."
