cd

mkdir ex1

touch ex1/file{1..5} 
# or: touch ex1/file1 ex1/file2 ex1/file3 ex1/file4 ex1/file5
# or: cd ex1; touch file{1..5}; cd ..
# or: for i in {1..5}; do touch ex1/file$i; done

ls -lt -h ex1

mkdir ex2
mv ex1/file{3..6} ex2

ls ex2
