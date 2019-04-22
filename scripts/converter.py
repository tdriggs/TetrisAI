import json

def parse_piece(piece_type):
    piece = [0]*7
    
    if piece_type == 0:
        return piece
    else:
        piece[piece_type-1] = 1
        return piece

def parse_frame(frame):
    output_depth = 6
    rows, cols = 20, 10
    board = frame['inputs']['gameBoard']
    curr = frame['inputs']['currentPiece']
    next = frame['inputs']['queuedPieces'][0]
    held = frame['inputs']['heldPiece']
    
    out_frame = frame['outputs']['frame']
    out_row = frame['outputs']['row']
    out_col = frame['outputs']['column']
    
    board_normalized = [1 if cell != 0 else 0 for cell in board]
    
    board2d = [[board_normalized[r*cols + c] for c in range(cols)] for r in range(rows)]
    
    test_input = board_normalized + parse_piece(curr) + parse_piece(next) + parse_piece(held)
    test_output = [0] * (output_depth * cols * 4 + 1)
    
    if out_frame == -1:
        test_output[-1] = 1
    else:
        heighest_row = rows
        for row_index, row in enumerate(board2d):
            for col in row:
                if col == 1:
                    heighest_row = row_index

        offset_row, offset_col = offset_array[curr-1][out_frame]
        relative_out_row = (out_row + offset_row) - heighest_row
        relative_out_col = out_col + offset_col
        
        relative_out_row = min(relative_out_row, output_depth-2) # -1 for one above, -1 for 0 counting
        
        frame_normalized = out_frame % frame_normalization_array[curr - 1]
        relative_out_row_normalized = relative_out_row + 1
        
        test_output[frame_normalized*output_depth*cols + relative_out_row_normalized*cols + relative_out_col] = 1
        
        print(curr, out_row, offset_row, relative_out_row, relative_out_row_normalized)
    
    return test_input, test_output

def main():
    with open("../recordings/alex_bad/good1.json", "r") as fp:
        inputs = json.load(fp)
        
    training = []
    
    for frame in inputs:
        test_input, test_output = parse_frame(frame)
        training.append({"input":test_input, "output":test_output})
        
        print(len(test_input), len(test_output))
    
    with open("../training/alex_bad/good1.csv", "w") as fp:
        for data_point in training:
            test_input = data_point['input']
            test_output = data_point['output']
            
            print(','.join(map(str, test_input + test_output)), file=fp)


#O = 1,I = 2,T = 3,S = 4,Z = 5,J = 6,L = 7    
frame_normalization_array = [
    1, 2, 4, 2, 2, 4, 4
]
    
#[piece][frame][row,col]
#O = 1,I = 2,T = 3,S = 4,Z = 5,J = 6,L = 7
offset_array = [
    #O
    [
        (2,1),
        (2,1),
        (2,1),
        (2,1)
    ],
    #I
    [
        (1,0),
        (3,2),
        (2,0),
        (0,1)
    ],
    #T
    [
        (2,0),
        (2,0),
        (1,0),
        (2,1)
    ],
    #S
    [
        (2,0),
        (2,0),
        (2,0),
        (2,0)
    ],
    #Z
    [
        (2,0),
        (2,1),
        (2,0),
        (2,1)
    ],
    #J
    [
        (2,0),
        (2,0),
        (1,0),
        (2,1)
    ],
    #L
    [
        (2,0),
        (2,0),
        (1,0),
        (2,1)
    ]
]
    
'''
// VOID == 0
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
	}),

	// O == 1
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		}),
	}),

	// I == 2
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			2, 2, 2, 2,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 2, 0,
			0, 0, 2, 0,
			0, 0, 2, 0,
			0, 0, 2, 0
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 0, 0, 0,
			2, 2, 2, 2,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 2, 0, 0,
			0, 2, 0, 0,
			0, 2, 0, 0,
			0, 2, 0, 0
		}),
	}),

	// T == 3
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			3, 3, 3, 0,
			0, 3, 0, 0,
			0, 0, 0, 0,
		}),
		Grid<4, 4>
		({
			0, 3, 0, 0,
			3, 3, 0, 0,
			0, 3, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 3, 0, 0,
			3, 3, 3, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 3, 0, 0,
			0, 3, 3, 0,
			0, 3, 0, 0,
			0, 0, 0, 0
		}),
	}),

	// S == 4
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 4, 4, 0,
			4, 4, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			4, 0, 0, 0,
			4, 4, 0, 0,
			0, 4, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 4, 4, 0,
			4, 4, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			4, 0, 0, 0,
			4, 4, 0, 0,
			0, 4, 0, 0,
			0, 0, 0, 0
		}),
	}),

	// Z == 5
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			5, 5, 0, 0,
			0, 5, 5, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 5, 0,
			0, 5, 5, 0,
			0, 5, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			5, 5, 0, 0,
			0, 5, 5, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 5, 0,
			0, 5, 5, 0,
			0, 5, 0, 0,
			0, 0, 0, 0
		}),
	}),

	// J == 6
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			6, 6, 6, 0,
			0, 0, 6, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 6, 0, 0,
			0, 6, 0, 0,
			6, 6, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			6, 0, 0, 0,
			6, 6, 6, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 6, 6, 0,
			0, 6, 0, 0,
			0, 6, 0, 0,
			0, 0, 0, 0
		}),
	}),

	// L == 7
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			7, 7, 7, 0,
			7, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			7, 7, 0, 0,
			0, 7, 0, 0,
			0, 7, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 7, 0,
			7, 7, 7, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 7, 0, 0,
			0, 7, 0, 0,
			0, 7, 7, 0,
			0, 0, 0, 0
		}),
}),
'''


if __name__ == "__main__":
    main()
