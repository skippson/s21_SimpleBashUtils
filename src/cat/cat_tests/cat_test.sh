#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""
TEST_FILE="test1.txt test2.txt"

for var in -e -n -s -t -b -v
do
            TEST1="$var $TEST_FILE"
            echo "$TEST1"
            ../s21_cat $TEST1 > s21_cat.txt
            cat $TEST1 > cat.txt
            DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
            if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
                then
                    (( SUCCESS++ ))
                else 
                    echo "$TEST1" >> log.txt
                    (( FAIL++ ))
                fi
                rm s21_cat.txt cat.txt
done

for var in -b -v -n -s -t -e
do
  for var2 in -v -e -n -s -t -b 
  do
        if [ $var != $var2 ]
        then
          TEST1="$var $var2 $TEST_FILE"
          echo "$TEST1"
          ../s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( FAIL++ ))
          fi
          rm s21_cat.txt cat.txt
        fi
  done
done

for var in -b -e -n -s -t -v 
do
  for var2 in -b -e -n -s -t -v 
  do
      for var3 in -b -e -n -s -t -v 
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST1="$var $var2 $var3 $TEST_FILE"
          echo "$TEST1"
          ../s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( FAIL++ ))
          fi
          rm s21_cat.txt cat.txt

        fi
      done
  done
done

for var in -b -e -n -s -t -v
do
  for var2 in -b -e -n -s -t -v 
  do
      for var3 in -b -e -n -s -t -v 
      do
          for var4 in -b -e -n -s -t -v 
          do
            if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
            then
              TEST1="$var $var2 $var3 $var4 $TEST_FILE"
              echo "$TEST1"
              ../s21_cat $TEST1 > s21_cat.txt
              cat $TEST1 > cat.txt
              DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
              if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
                then
                  (( SUCCESS++ ))
                else
                  echo "$TEST1" >> log.txt
                  (( FAIL++ ))
              fi
              rm s21_cat.txt cat.txt

            fi
          done
      done
  done
done

echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"