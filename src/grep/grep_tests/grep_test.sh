#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""
TEST_FILE="ya test1.txt test2.txt"
TEST_FILE_S="-s ya test1.txt nofile test2.txt"
TEST_FILE_F="-f test_pattern_file.txt test1.txt test2.txt"
TEST_FILE_E="-e ya -e smoke test1.txt test2.txt"
TEST_FILE_E_F="-f test_pattern_file.txt -e zoomer test1.txt test2.txt"

for var in -i -v -c -n -l -o -h 
do 
            TEST1="$var $TEST_FILE"
            echo "$TEST1"
            ../s21_grep $TEST1 > s21_grep.txt
            grep $TEST1 > grep.txt
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                then
                    (( SUCCESS++ ))
                else 
                    echo "$TEST1" >> log.txt
                    (( FAIL++ ))
                fi
                rm s21_grep.txt grep.txt
done

for var in -i -v -c -n -l -o -h
do
  for var2 in -i -v -c -n -l -o -h
  do
        if [ $var != $var2 ]
        then
          TEST1="$var $var2 $TEST_FILE"
          echo "$TEST1"
          ../s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( FAIL++ ))
          fi
          rm s21_grep.txt grep.txt
        fi
  done
done

for var in -i -v -c -n -l -o -h
do
  for var2 in -i -v -c -n -l -o -h 
  do
      for var3 in -i -v -c -n -l -o -h 
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST1="$var $var2 $var3 $TEST_FILE"
          echo "$TEST1"
          ../s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( FAIL++ ))
          fi
          rm s21_grep.txt grep.txt

        fi
      done
  done
done

for var in -i -v -c -n -l -o -h
do
  for var2 in -i -v -c -n -l -o -h 
  do
      for var3 in -i -v -c -n -l -o -h 
      do
          for var4 in -i -v -c -n -l -o -h 
          do
            if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
            then
              TEST1="$var $var2 $var3 $var4 $TEST_FILE"
              echo "$TEST1"
              ../s21_grep $TEST1 > s21_grep.txt
              grep $TEST1 > grep.txt
              DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
              if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                then
                  (( SUCCESS++ ))
                else
                  echo "$TEST1" >> log.txt
                  (( FAIL++ ))
              fi
              rm s21_grep.txt grep.txt

            fi
          done
      done
  done
done

for var in -i -v -c -n -l -o -h 
do 
            TEST1="$var $TEST_FILE_S"
            echo "$TEST1"
            ../s21_grep $TEST1 > s21_grep.txt
            grep $TEST1 > grep.txt
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                then
                    (( SUCCESS++ ))
                else 
                    echo "$TEST1" >> log.txt
                    (( FAIL++ ))
                fi
                rm s21_grep.txt grep.txt
done

for var in -i -v -c -n -l -o -h 
do 
            TEST1="$var $TEST_FILE_F"
            echo "$TEST1"
            ../s21_grep $TEST1 > s21_grep.txt
            grep $TEST1 > grep.txt
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                then
                    (( SUCCESS++ ))
                else 
                    echo "$TEST1" >> log.txt
                    (( FAIL++ ))
                fi
                rm s21_grep.txt grep.txt
done

for var in -i -v -c -n -l -o -h 
do 
            TEST1="$var $TEST_FILE_E"
            echo "$TEST1"
            ../s21_grep $TEST1 > s21_grep.txt
            grep $TEST1 > grep.txt
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                then
                    (( SUCCESS++ ))
                else 
                    echo "$TEST1" >> log.txt
                    (( FAIL++ ))
                fi
                rm s21_grep.txt grep.txt
done

for var in -i -v -c -n -l -o -h 
do 
            TEST1="$var $TEST_FILE_E_F"
            echo "$TEST1"
            ../s21_grep $TEST1 > s21_grep.txt
            grep $TEST1 > grep.txt
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                then
                    (( SUCCESS++ ))
                else 
                    echo "$TEST1" >> log.txt
                    (( FAIL++ ))
                fi
                rm s21_grep.txt grep.txt
done

echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"