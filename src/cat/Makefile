CC = gcc

CFLAGS = -std=c11 -Werror -Wall -Wextra

all : s21_cat

rebuild : all

s21_cat : clear
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

clear : 
	rm -rf s21_cat
