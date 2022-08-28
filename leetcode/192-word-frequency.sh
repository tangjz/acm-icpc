# Read from the file words.txt and output the word frequency list to stdout.
cat words.txt | xargs printf "%s\n" | sort | uniq -c | sort -r | awk '{ print $2, $1 }'
