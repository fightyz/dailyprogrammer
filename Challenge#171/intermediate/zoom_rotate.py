 # http://www.reddit.com/r/dailyprogrammer/comments/2avd5i/7162014_challenge_171_intermediate_zoom_rotate/

class TextBitmap:
	def __init__(self, data):
		self.__data = [self.__create_image(row) for row in data.split()]

	def __create_image(self, value):
		return bin(int(value, 16))[2:].rjust(8, '0')

	def display(self):
		for row in self.__data:
			for _ in range(len(row) // 8):
				print(row.translate(str.maketrans("01", " *")))

	def zoom(self, scale):
		if 0 < scale <= 4 and scale != 3 and len(self.__data[0]) * scale <= 32:
			self.__data = ["".join([c * scale for c in row]) for row in self.__data]
		elif -4 <= scale < 0 and scale != -3 and len(self.__data[0]) / -scale >= 8:
			self.__data = ["".join([c for c in row[::-scale]]) for row in self.__data]

	def rotate(self, degrees, clockwise = True):
		if clockwise:
			degrees = 360 - degrees
		for _ in range(degrees // 90):
			self.__rotate90_counterclockwise()

	def __rotate90_counterclockwise(self):
		scale = len(self.__data[0]) // 8
		self.zoom(-scale)
		self.__data = ["".join([row[7 - n] for row in self.__data]) for n in range(8)]
		self.zoom(scale)

	def invert(self):
		self.__data = [row.translate(str.maketrans("01", "10")) for row in self.__data]

def main():
	for line in open("hex_images.txt"):
		img = TextBitmap(line)
		transformations = "img.zoom(2) img.rotate(90) img.zoom(2) img.invert() img.zoom(-2)"
		for transformation in transformations.split():
			eval(transformation)
			img.display()


if __name__ == '__main__':
 	main()