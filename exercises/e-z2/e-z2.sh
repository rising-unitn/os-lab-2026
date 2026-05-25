curl https://www.gutenberg.org/cache/epub/1012/pg1012.txt -o divina_commedia.txt
grep "Canto" divina_commedia.txt | grep "Inferno" | wc -l
grep "Canto" divina_commedia.txt | grep "Purgatorio" | wc -l
grep "Canto" divina_commedia.txt | grep "Paradiso" | wc -l
grep "Canto" divina_commedia.txt -A 5 | grep -v "Canto"
grep -o "quanto" divina_commedia.txt | wc -l
