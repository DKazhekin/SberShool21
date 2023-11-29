#!/bin/bash

make s21_grep

#1 test for several -e flags
./s21_grep -e line -e today mega_test.txt > my_grep.txt
grep -e today -e line mega_test.txt > actual_grep.txt
diff actual_grep.txt my_grep.txt
if [ $? -eq 0 ]; then
      echo "Grep -e test passed!"
  else
      echo "Grep -e test failed!"
fi


#2 tests for -i flag
./s21_grep -i BYE mega_test.txt > my_grep.txt
grep -i BYE mega_test.txt > actual_grep.txt
diff actual_grep.txt my_grep.txt
if [ $? -eq 0 ]; then
      echo "Grep 1st -i test passed!"
  else
      echo "Grep 1st -e test failed!"
fi

./s21_grep -i ENOUGH mega_test.txt mega_test2.txt > my_grep.txt
grep -i ENOUGH mega_test.txt mega_test2.txt > actual_grep.txt
diff actual_grep.txt my_grep.txt
if [ $? -eq 0 ]; then
      echo "Grep 2nd -i test passed!"
  else
      echo "Grep 2nd -e test failed!"
fi

#3 test for -v flag
./s21_grep -v "good weather" mega_test.txt mega_test2.txt mega_test3.txt > my_grep.txt
grep -v "good weather" mega_test.txt mega_test2.txt mega_test3.txt > actual_grep.txt
diff actual_grep.txt my_grep.txt
if [ $? -eq 0 ]; then
      echo "Grep -v test passed!"
  else
      echo "Grep -v test failed!"
fi

#4 test for -ci flag
./s21_grep -ci BYE mega_test.txt mega_test2.txt > my_grep.txt
grep -ci BYE mega_test.txt mega_test2.txt > actual_grep.txt
diff actual_grep.txt my_grep.txt
if [ $? -eq 0 ]; then
      echo "Grep -ci test passed!"
  else
      echo "Grep -ci test failed!"
fi

#5 test for -l flag
./s21_grep -l first mega_test.txt mega_test2.txt mega_test3.txt > my_grep.txt
grep -l first mega_test.txt mega_test2.txt mega_test3.txt > actual_grep.txt
diff actual_grep.txt my_grep.txt
if [ $? -eq 0 ]; then
      echo "Grep -l test passed!"
  else
      echo "Grep -l test failed!"
fi

#6 test for -ni flag
./s21_grep -ni GonnA mega_test.txt mega_test2.txt mega_test3.txt > my_grep.txt
grep -ni GonnA mega_test.txt mega_test2.txt mega_test3.txt > actual_grep.txt
diff actual_grep.txt my_grep.txt
if [ $? -eq 0 ]; then
      echo "Grep -ni test passed!"
  else
      echo "Grep -ni test failed!"
fi

rm -rf actual_grep.txt my_grep.txt s21_grep