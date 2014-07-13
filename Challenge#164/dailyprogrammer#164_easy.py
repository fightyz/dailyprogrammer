#!/usr/bin/python

def task_2():
	count, tmp = 1, 0
	a = []
	while count <= 100:
		tmp += 15
		a.append(tmp)
		count += 1
	return a

def task_3():
	word_1 = raw_input("input word_1:")
	word_2 = raw_input("input word_2:")
	flag = 0
	table = {'a':0, 'b':0, 'c':0, 'd':0, 'e':0, 'f':0, 'g':0, 'h':0, 'i':0,\
			 'j':0, 'k':0, 'l':0, 'm':0, 'n':0, 'o':0, 'p':0, 'q':0, 'r':0,\
			 's':0, 't':0, 'u':0, 'v':0, 'w':0, 'x':0, 'y':0, 'z':0}
	for i in range(len(word_1)):
		table[word_1[i]] += 1
	for i in range(len(word_2)):
		table[word_2[i]] -= 1
	for i in table:
		if table[i] != 0:
			flag = 1
			break
	if flag == 0:
		print 'Yes, %s is an anagram of %s' %(word_1, word_2)
	else:
		print 'No, %s is not an anagram of %s' %(word_1, word_2)

def task_4():
	word = raw_input("input word:")
	letter = raw_input("input a letter:")
	tmp = word.replace(letter, '')
	print (tmp)

def task_5():
	array = []
	sum = 0
	print 'input an array of integers, end by 0:'
	string = raw_input()
	integer = int(string)
	while integer != 0:
		array.append(integer)
		string = raw_input();
		integer = int(string)
	for x in array:
		sum += x
	print(sum)

def bubble_sort(array):
	for i in range(len(array)):
		for j in range(len(array) - i - 1):
			if array[j] > array[j + 1]:
				tmp =  array[j + 1]
				array[j + 1] = array[j]
				array[j] = tmp
	print(array)

# task 1
print 'Task 1:'
print 'Hello World'

#task 2
print 'Task 2:'
array = task_2()
for x in array:
	print x,

#task 3
print '\nTask 3:'
task_3()

#task 4
print 'Task 4:'
task_4()

#task 5
print 'Task 5:'
task_5()

#bonus
print 'Bonus:'
array = [5,7,4,1, 8]
bubble_sort(array)