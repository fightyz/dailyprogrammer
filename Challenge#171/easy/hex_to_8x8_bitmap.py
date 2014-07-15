# http://www.reddit.com/r/dailyprogrammer/comments/2ao99p/7142014_challenge_171_easy_hex_to_8x8_bitmap/

def create_bitmap_row(hex_str):
	bin_str = str(bin(int(hex_str, 16)))[2:].rjust(8)

	table = str.maketrans('01', ' X')
	bitmap = bin_str.translate(table)

	return bitmap

def main():
	input_ = input('Enter hex numbers (0 - FF) seperated by spaces: ')

	for element in input_.split():
		print(create_bitmap_row(element))

if __name__ == '__main__':
	main()