# Read from the file file.txt and print its transposed content to stdout.
head -n 1 file.txt | wc -w | xargs seq | xargs -i bash -c "cut -d ' ' -f {} file.txt | paste -sd ' '"
