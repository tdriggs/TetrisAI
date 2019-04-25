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
			-2: (3, 3, 9),
			-1: (3, 3, 8),
			0: (3, 3, 7),
			1: (3, 3, 6),
			2: (3, 3, 5),
			3: (3, 3, 4),
			4: (3, 3, 3),
			5: (3, 3, 2),
			6: (3, 3, 1),
			7: (3, 3, 0),
			8: (3, 3, -1)
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
			-2: (3, 1, 9),
			-1: (3, 1, 8),
			0: (3, 1, 7),
			1: (3, 1, 6),
			2: (3, 1, 5),
			3: (3, 1, 4),
			4: (3, 1, 3),
			5: (3, 1, 2),
			6: (3, 1, 1),
			7: (3, 1, 0),
			8: (3, 1, -1)
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
			-2: (7, 3, 9),
			-1: (7, 3, 8),
			0: (7, 3, 7),
			1: (7, 3, 6),
			2: (7, 3, 5),
			3: (7, 3, 4),
			4: (7, 3, 3),
			5: (7, 3, 2),
			6: (7, 3, 1),
			7: (7, 3, 0),
			8: (7, 3, -1)
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
			-2: (7, 1, 9),
			-1: (7, 1, 8),
			0: (7, 1, 7),
			1: (7, 1, 6),
			2: (7, 1, 5),
			3: (7, 1, 4),
			4: (7, 1, 3),
			5: (7, 1, 2),
			6: (7, 1, 1),
			7: (7, 1, 0),
			8: (7, 1, -1)
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
			-2: (6, 3, 9),
			-1: (6, 3, 8),
			0: (6, 3, 7),
			1: (6, 3, 6),
			2: (6, 3, 5),
			3: (6, 3, 4),
			4: (6, 3, 3),
			5: (6, 3, 2),
			6: (6, 3, 1),
			7: (6, 3, 0),
			8: (6, 3, -1)
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
			-2: (6, 1, 9),
			-1: (6, 1, 8),
			0: (6, 1, 7),
			1: (6, 1, 6),
			2: (6, 1, 5),
			3: (6, 1, 4),
			4: (6, 1, 3),
			5: (6, 1, 2),
			6: (6, 1, 1),
			7: (6, 1, 0),
			8: (6, 1, -1)
		}
	}
}


def flip(entry):
	if entry['outputs']['frame'] == -1:
		return None

	new_input_board = flip_board(entry['inputs']['gameBoard'])
	new_piece, new_frame, new_column = result_table[entry['inputs']['currentPiece']][entry['outputs']['frame']][entry['outputs']['column']]
	new_entry = {}
	new_entry['inputs'] = {}
	new_entry['inputs']['gameBoard'] = new_input_board
	new_entry['inputs']['currentPiece'] = new_piece
	new_entry['inputs']['heldPiece'] = entry['inputs']['heldPiece']
	new_entry['inputs']['queuedPieces'] = entry['inputs']['queuedPieces']
	new_entry['outputs'] = {}
	new_entry['outputs']['row'] = entry['outputs']['row']
	new_entry['outputs']['column'] = new_column
	new_entry['outputs']['frame'] = new_frame

	return new_entry


def add_incomplete_row(num_missing_blocks, entry, row_above, num_available_blocks):
	chance_empty = max(min(num_missing_blocks / num_available_blocks, 1), 0)
	empty_indices = []
	available_indices = [i for i in range(len(row_above)) if row_above[i] != 0]
	for i in range(num_missing_blocks):
		if len(available_indices) != 0:
			index = random.choice(available_indices)
			available_indices.remove(index)
			empty_indices.append(index)
		else:
			return None

	new_row = [0 if i in empty_indices else 1 for i in range(len(row_above))]

	new_entry = {}
	new_entry['inputs'] = {}
	new_entry['inputs']['gameBoard'] = entry['inputs']['gameBoard'][10:]
	new_entry['inputs']['gameBoard'] += new_row
	new_entry['inputs']['currentPiece'] = entry['inputs']['currentPiece']
	new_entry['inputs']['heldPiece'] = entry['inputs']['heldPiece']
	new_entry['inputs']['queuedPieces'] = entry['inputs']['queuedPieces']
	new_entry['outputs'] = {}
	new_entry['outputs']['row'] = entry['outputs']['row'] - 1
	new_entry['outputs']['column'] = entry['outputs']['column']
	new_entry['outputs']['frame'] = entry['outputs']['frame']

	return new_entry


def add_incomplete_rows(num_rows, num_missing_blocks, entry):
	row_above = entry['inputs']['gameBoard'][-10:]
	num_available_blocks = len(row_above) - row_above.count(0)
	if num_available_blocks > 0:
		curr_entry = entry
		for i in range(num_rows):
			row_above = curr_entry['inputs']['gameBoard'][-10:]
			num_available_blocks = len(row_above) - row_above.count(0)
			curr_entry = add_incomplete_row(num_missing_blocks, curr_entry, row_above, num_available_blocks)
			if curr_entry is None:
				break

		return curr_entry
	return None


if __name__ == "__main__":
	original_entries = []
	extra_rows = {}
	flipped_rows = []
	flipped_extra_rows = {}

	alex_files = ['../training_data_raw/Alex/' + f for f in os.listdir('../training_data_raw/Alex')]
	kory_files = ['../training_data_raw/Kory/' + f for f in os.listdir('../training_data_raw/Kory')]
	liam_files = ['../training_data_raw/Liam/' + f for f in os.listdir('../training_data_raw/Liam')]

	max_num_extra_rows = 5
	max_num_missing_blocks = 1

	files = alex_files + kory_files + liam_files
	for f in files:
		with open(f, 'r') as infile:
			obj = json.load(infile)
			for e in obj:
				original_entries.append(e)

				for j in range(1, max_num_extra_rows + 1):
					if j not in extra_rows:
						extra_rows[j] = {}
					for i in range(1, max_num_missing_blocks + 1):
						if i not in extra_rows[j]:
							extra_rows[j][i] = []
						new_entry = add_incomplete_rows(j, i, e)
						if new_entry != None:
							extra_rows[j][i].append(new_entry)
						else:
							break

				flipped = flip(e)
				if flipped != None:
					flipped_rows.append(flipped)

					for j in range(1, max_num_extra_rows + 1):
						if j not in flipped_extra_rows:
							flipped_extra_rows[j] = {}
						for i in range(1, max_num_missing_blocks + 1):
							if i not in flipped_extra_rows[j]:
								flipped_extra_rows[j][i] = []
							new_entry = add_incomplete_rows(j, i, e)
							if new_entry != None:
								flipped_extra_rows[j][i].append(new_entry)
							else:
								break

	for num_rows in extra_rows:
		for num_missing in extra_rows[num_rows]:
			with open('../training_data_raw/modified/extra_rows_{}_{}.json'.format(num_rows, num_missing), 'w') as outfile:
				json.dump(extra_rows[num_rows][num_missing], outfile, indent=2, separators=(',', ': '))

	with open('../training_data_raw/modified/flipped_rows.json', 'w') as outfile:
		json.dump(flipped_rows, outfile, indent=2, separators=(',', ': '))

	for num_rows in extra_rows:
		for num_missing in extra_rows[num_rows]:
			with open('../training_data_raw/modified/flipped_extra_rows_{}_{}.json'.format(num_rows, num_missing), 'w') as outfile:
				json.dump(flipped_extra_rows[num_rows][num_missing], outfile, indent=2, separators=(',', ': '))
