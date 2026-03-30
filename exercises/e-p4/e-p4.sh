mkdir -p project/src project/docs project/build

touch project/src/main.c project/src/utils.c project/src/utils.h
touch project/docs/README.md

cp project/src/*.c project/build

ls project/build
# main.c  utils.c

rm -r project/build

mv project/docs project/documentation
