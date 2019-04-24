import json
import random
import os


def flip_row(row):
	return reversed(row)


def flip_board(board):
	new_board = []
	for i in range(0, 20):
		new_board += flip_row(board[i*10:(i+1)*10])
	return new_board


# piece: {frame: {column: result(pfc)}}
result_table = {
	1: { # O - same frame, same block
		0: {
			-2: (1, 0, 8),
			-1: (1, 0, 7),
			0: (1, 0, 6),
			1: (1, 0, 5),
			2: (1, 0, 4),
			3: (1, 0, 3),
			4: (1, 0, 2),
			5: (1, 0, 1),
			6: (1, 0, 0),
			7: (1, 0, -1),
			8: (1, 0, -2)
		},
		1: {
			-2: (1, 1, 8),
			-1: (1, 1, 7),
			0: (1, 1, 6),
			1: (1, 1, 5),
			2: (1, 1, 4),
			3: (1, 1, 3),
			4: (1, 1, 2),
			5: (1, 1, 1),
			6: (1, 1, 0),
			7: (1, 1, -1),
			8: (1, 1, -2)
		},
		2: {
			-2: (1, 2, 8),
			-1: (1, 2, 7),
			0: (1, 2, 6),
			1: (1, 2, 5),
			2: (1, 2, 4),
			3: (1, 2, 3),
			4: (1, 2, 2),
			5: (1, 2, 1),
			6: (1, 2, 0),
			7: (1, 2, -1),
			8: (1, 2, -2)
		},
		3: {
			-2: (1, 3, 8),
			-1: (1, 3, 7),
			0: (1, 3, 6),
			1: (1, 3, 5),
			2: (1, 3, 4),
			3: (1, 3, 3),
			4: (1, 3, 2),
			5: (1, 3, 1),
			6: (1, 3, 0),
			7: (1, 3, -1),
			8: (1, 3, -2)
		}
	},
	2: { # I, same block, flip frames 1 and 3
		0: {
			-2: (2, 0, 8),
			-1: (2, 0, 7),
			0: (2, 0, 6),
			1: (2, 0, 5),
			2: (2, 0, 4),
			3: (2, 0, 3),
			4: (2, 0, 2),
			5: (2, 0, 1),
			6: (2, 0, 0),
			7: (2, 0, -1),
			8: (2, 0, -2)
		},
		1: {
			-2: (2, 3, 8),
			-1: (2, 3, 7),
			0: (2, 3, 6),
			1: (2, 3, 5),
			2: (2, 3, 4),
			3: (2, 3, 3),
			4: (2, 3, 2),
			5: (2, 3, 1),
			6: (2, 3, 0),
			7: (2, 3, -1),
			8: (2, 3, -2)
		},
		2: {
			-2: (2, 2, 8),
			-1: (2, 2, 7),
			0: (2, 2, 6),
			1: (2, 2, 5),
			2: (2, 2, 4),
			3: (2, 2, 3),
			4: (2, 2, 2),
			5: (2, 2, 1),
			6: (2, 2, 0),
			7: (2, 2, -1),
			8: (2, 2, -2)
		},
		3: {
			-2: (2, 1, 8),
			-1: (2, 1, 7),
			0: (2, 1, 6),
			1: (2, 1, 5),
			2: (2, 1, 4),
			3: (2, 1, 3),
			4: (2, 1, 2),
			5: (2, 1, 1),
			6: (2, 1, 0),
			7: (2, 1, -1),
			8: (2, 1, -2)
		}
	},
	3: { # T - same block, switch frames 1 and 3
		0: {
			-2: (3, 0, 9),
			-1: (3, 0, 8),
			0: (3, 0, 7),
			1: (3, 0, 6),
			2: (3, 0, 5),
			3: (3, 0, 4),
			4: (3, 0, 3),
			5: (3, 0, 2),
			6: (3, 0, 1),
			7: (3, 0, 0),
			8: (3, 0, -1)
		},
		1: {
			-2: (3, 3, 10),
			-1: (3, 3, 9),
			0: (3, 3, 8),
			1: (3, 3, 7),
			2: (3, 3, 6),
			3: (3, 3, 5),
			4: (3, 3, 4),
			5: (3, 3, 3),
			6: (3, 3, 2),
			7: (3, 3, 1),
			8: (3, 3, 0)
		},
		2: {
			-2: (3, 2, 9),
			-1: (3, 2, 8),
			0: (3, 2, 7),
			1: (3, 2, 6),
			2: (3, 2, 5),
			3: (3, 2, 4),
			4: (3, 2, 3),
			5: (3, 2, 2),
			6: (3, 2, 1),
			7: (3, 2, 0),
			8: (3, 2, -1)
		},
		3: {
			-2: (3, 1, 10),
			-1: (3, 1, 9),
			0: (3, 1, 8),
			1: (3, 1, 7),
			2: (3, 1, 6),
			3: (3, 1, 5),
			4: (3, 1, 4),
			5: (3, 1, 3),
			6: (3, 1, 2),
			7: (3, 1, 1),
			8: (3, 1, 0)
		}
	},
	4: { # S - switch to Z, frames stay the same
		0: {
			-2: (5, 0, 9),
			-1: (5, 0, 8),
			0: (5, 0, 7),
			1: (5, 0, 6),
			2: (5, 0, 5),
			3: (5, 0, 4),
			4: (5, 0, 3),
			5: (5, 0, 2),
			6: (5, 0, 1),
			7: (5, 0, 0),
			8: (5, 0, -1)
		},
		1: {
			-2: (5, 1, 9),
			-1: (5, 1, 8),
			0: (5, 1, 7),
			1: (5, 1, 6),
			2: (5, 1, 5),
			3: (5, 1, 4),
			4: (5, 1, 3),
			5: (5, 1, 2),
			6: (5, 1, 1),
			7: (5, 1, 0),
			8: (5, 1, -1)
		},
		2: {
			-2: (5, 2, 9),
			-1: (5, 2, 8),
			0: (5, 2, 7),
			1: (5, 2, 6),
			2: (5, 2, 5),
			3: (5, 2, 4),
			4: (5, 2, 3),
			5: (5, 2, 2),
			6: (5, 2, 1),
			7: (5, 2, 0),
			8: (5, 2, -1)
		},
		3: {
			-2: (5, 3, 9),
			-1: (5, 3, 8),
			0: (5, 3, 7),
			1: (5, 3, 6),
			2: (5, 3, 5),
			3: (5, 3, 4),
			4: (5, 3, 3),
			5: (5, 3, 2),
			6: (5, 3, 1),
			7: (5, 3, 0),
			8: (5, 3, -1)
		}
	},
	5: { # Z - switch to s, frame remains the same
		0: {
			-2: (4, 0, 9),
			-1: (4, 0, 8),
			0: (4, 0, 7),
			1: (4, 0, 6),
			2: (4, 0, 5),
			3: (4, 0, 4),
			4: (4, 0, 3),
			5: (4, 0, 2),
			6: (4, 0, 1),
			7: (4, 0, 0),
			8: (4, 0, -1)
		},
		1: {
			-2: (4, 1, 9),
			-1: (4, 1, 8),
			0: (4, 1, 7),
			1: (4, 1, 6),
			2: (4, 1, 5),
			3: (4, 1, 4),
			4: (4, 1, 3),
			5: (4, 1, 2),
			6: (4, 1, 1),
			7: (4, 1, 0),
			8: (4, 1, -1)
		},
		2: {
			-2: (4, 2, 9),
			-1: (4, 2, 8),
			0: (4, 2, 7),
			1: (4, 2, 6),
			2: (4, 2, 5),
			3: (4, 2, 4),
			4: (4, 2, 3),
			5: (4, 2, 2),
			6: (4, 2, 1),
			7: (4, 2, 0),
			8: (4, 2, -1)
		},
		3: {
			-2: (4, 3, 9),
			-1: (4, 3, 8),
			0: (4, 3, 7),
			1: (4, 3, 6),
			2: (4, 3, 5),
			3: (4, 3, 4),
			4: (4, 3, 3),
			5: (4, 3, 2),
			6: (4, 3, 1),
			7: (4, 3, 0),
			8: (4, 3, -1)
		}
	},
	6: {
		0: {
			-2: (7, 0, 9),
			-1: (7, 0, 8),
			0: (7, 0, 7),
			1: (7, 0, 6),
			2: (7, 0, 5),
			3: (7, 0, 4),
			4: (7, 0, 3),
			5: (7, 0, 2),
			6: (7, 0, 1),
			7: (7, 0, 0),
			8: (7, 0, -1)
		},
		1: {
			-2: (7, 1, 10),
			-1: (7, 1, 9),
			0: (7, 1, 8),
			1: (7, 1, 7),
			2: (7, 1, 6),
			3: (7, 1, 5),
			4: (7, 1, 4),
			5: (7, 1, 3),
			6: (7, 1, 2),
			7: (7, 1, 1),
			8: (7, 1, 0)
		},
		2: {
			-2: (7, 2, 9),
			-1: (7, 2, 8),
			0: (7, 2, 7),
			1: (7, 2, 6),
			2: (7, 2, 5),
			3: (7, 2, 4),
			4: (7, 2, 3),
			5: (7, 2, 2),
			6: (7, 2, 1),
			7: (7, 2, 0),
			8: (7, 2, -1)
		},
		3: {
			-2: (7, 3, 10),
			-1: (7, 3, 9),
			0: (7, 3, 8),
			1: (7, 3, 7),
			2: (7, 3, 6),
			3: (7, 3, 5),
			4: (7, 3, 4),
			5: (7, 3, 3),
			6: (7, 3, 2),
			7: (7, 3, 1),
			8: (7, 3, 0)
		}
	},
	7: {
		0: {
			-2: (6, 0, 9),
			-1: (6, 0, 8),
			0: (6, 0, 7),
			1: (6, 0, 6),
			2: (6, 0, 5),
			3: (6, 0, 4),
			4: (6, 0, 3),
			5: (6, 0, 2),
			6: (6, 0, 1),
			7: (6, 0, 0),
			8: (6, 0, -1)
		},
		1: {
			-2: (6, 1, 10),
			-1: (6, 1, 9),
			0: (6, 1, 8),
			1: (6, 1, 7),
			2: (6, 1, 6),
			3: (6, 1, 5),
			4: (6, 1, 4),
			5: (6, 1, 3),
			6: (6, 1, 2),
			7: (6, 1, 1),
			8: (6, 1, 0)
		},
		2: {
			-2: (6, 2, 9),
			-1: (6, 2, 8),
			0: (6, 2, 7),
			1: (6, 2, 6),
			2: (6, 2, 5),
			3: (6, 2, 4),
			4: (6, 2, 3),
			5: (6, 2, 2),
			6: (6, 2, 1),
			7: (6, 2, 0),
			8: (6, 2, -1)
		},
		3: {
			-2: (6, 3, 10),
			-1: (6, 3, 9),
			0: (6, 3, 8),
			1: (6, 3, 7),
			2: (6, 3, 6),
			3: (6, 3, 5),
			4: (6, 3, 4),
			5: (6, 3, 3),
			6: (6, 3, 2),
			7: (6, 3, 1),
			8: (6, 3, 0)
		}
	}
}


def flip(entry):
	if entry['outputs']['frame'] == -1:
		return None

	new_input_board = flip_board(entry['inputs']['gameBoard'])
	new_piece, new_frame, new_column = result_table[entry['inputs']['currentPiece']][entry['outputs']['frame']][entry['outputs']['column']]
	entry['inputs']['gameBoard'] = new_input_board
	entry['inputs']['currentPiece'] = new_piece
	entry['outputs']['frame'] = new_frame
	entry['outputs']['column'] = new_column

	return entry


def add_incomplete_row(num_missing_blocks, entry):
	row_above = entry['inputs']['gameBoard'][-10:]
	num_available_blocks = len(row_above) - row_above.count(0)
	if num_available_blocks > 0:
		chance_empty = max(min(num_missing_blocks / num_available_blocks, 1), 0)
		new_row = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
		for i in range(len(new_row)):
			if row_above[i] != 0:
				if random.uniform(0, 1) < chance_empty:
					new_row[i] = 0

		entry['inputs']['gameBoard'] = entry['inputs']['gameBoard'][10:]
		entry['inputs']['gameBoard'] += new_row
		return entry
	return None

if __name__ == "__main__":
	original_entries = []
	one_extra_row = []
	two_extra_rows = []
	three_extra_rows = []
	four_extra_rows = []
	flipped_rows = []
	one_extra_flipped = []
	two_extra_flipped = []
	three_extra_flipped = []
	four_extra_flipped = []

	alex_files = ['../training_data_raw/Alex/' + f for f in os.listdir('../training_data_raw/Alex')]
	kory_files = ['../training_data_raw/Kory/' + f for f in os.listdir('../training_data_raw/Kory')]
	liam_files = ['../training_data_raw/Liam/' + f for f in os.listdir('../training_data_raw/Liam')]

	files = alex_files + kory_files + liam_files
	for f in files:
		with open(f, 'r') as infile:
			obj = json.load(infile)
			for e in obj:
				original_entries.append(e)

				one_extra = add_incomplete_row(5, e)
				if one_extra != None:
					one_extra_row.append(one_extra)

				two_extra = add_incomplete_row(5, e)
				if two_extra != None:
					two_extra = add_incomplete_row(5, two_extra)
					if two_extra != None:
						two_extra_rows.append(two_extra)

				three_extra = add_incomplete_row(5, e)			
				if two_extra != None:
					three_extra = add_incomplete_row(5, three_extra)
					if three_extra != None:
						three_extra = add_incomplete_row(5, three_extra)
						if three_extra != None:
							three_extra_rows.append(three_extra)

				four_extra = add_incomplete_row(5, e)
				if three_extra != None:
					four_extra = add_incomplete_row(5, four_extra)
					if three_extra != None:
						four_extra = add_incomplete_row(5, four_extra)
						if three_extra != None:
							four_extra = add_incomplete_row(5, four_extra)
							if four_extra != None:
								four_extra_rows.append(four_extra)

				flipped = flip(e)
				if flipped != None:
					flipped_rows.append(flipped)

					one_extra = add_incomplete_row(5, flipped)
					if one_extra != None:
						one_extra_flipped.append(one_extra)

					two_extra = add_incomplete_row(5, flipped)
					if two_extra != None:
						two_extra = add_incomplete_row(5, two_extra)
						if two_extra != None:
							two_extra_flipped.append(two_extra)

					three_extra = add_incomplete_row(5, flipped)			
					if two_extra != None:
						three_extra = add_incomplete_row(5, three_extra)
						if three_extra != None:
							three_extra = add_incomplete_row(5, three_extra)
							if three_extra != None:
								three_extra_flipped.append(three_extra)

					four_extra = add_incomplete_row(5, flipped)
					if three_extra != None:
						four_extra = add_incomplete_row(5, four_extra)
						if three_extra != None:
							four_extra = add_incomplete_row(5, four_extra)
							if three_extra != None:
								four_extra = add_incomplete_row(5, four_extra)
								if four_extra != None:
									four_extra_flipped.append(four_extra)

	with open('../training_data_raw/modified/one_extra_row.json', 'w') as outfile:
		json.dump(one_extra_row, outfile, indent=2, separators=(',', ': '))

	with open('../training_data_raw/modified/two_extra_rows.json', 'w') as outfile:
		json.dump(two_extra_rows, outfile, indent=2, separators=(',', ': '))

	with open('../training_data_raw/modified/three_extra_rows.json', 'w') as outfile:
		json.dump(three_extra_rows, outfile, indent=2, separators=(',', ': '))

	with open('../training_data_raw/modified/four_extra_rows.json', 'w') as outfile:
		json.dump(four_extra_rows, outfile, indent=2, separators=(',', ': '))

	with open('../training_data_raw/modified/flipped.json', 'w') as outfile:
		json.dump(flipped_rows, outfile, indent=2, separators=(',', ': '))

	with open('../training_data_raw/modified/one_extra_flipped.json', 'w') as outfile:
		json.dump(one_extra_flipped, outfile, indent=2, separators=(',', ': '))

	with open('../training_data_raw/modified/two_extra_flipped.json', 'w') as outfile:
		json.dump(two_extra_flipped, outfile, indent=2, separators=(',', ': '))

	with open('../training_data_raw/modified/three_extra_flipped.json', 'w') as outfile:
		json.dump(three_extra_flipped, outfile, indent=2, separators=(',', ': '))

	with open('../training_data_raw/modified/four_extra_flipped.json', 'w') as outfile:
		json.dump(four_extra_flipped, outfile, indent=2, separators=(',', ': '))
