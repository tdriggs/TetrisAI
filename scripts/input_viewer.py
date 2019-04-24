import pygame, json, random


ROWS = 20
COLUMNS = 10

# 0=Empty-White, 1=T-Purple, 2=I-Cyan, 3=O-Yellow, 4=L-Orange, 5=J-Blue, 6=S-Green, 7=Z-Red
COLORS = [
    (255,255,255),
    (200,0,200),
    (0,150,200),
    (250,250,0),
    (250,150,0),
    (0,0,255),
    (0,255,0),
    (255,0,0)
]



frames = {
    1: {
        0: [
            (0, 0, 0, 0),
            (0, 1, 1, 0),
            (0, 1, 1, 0),
            (0, 0, 0, 0)
        ],
        1: [
            (0, 0, 0, 0),
            (0, 1, 1, 0),
            (0, 1, 1, 0),
            (0, 0, 0, 0)
        ],
        2: [
            (0, 0, 0, 0),
            (0, 1, 1, 0),
            (0, 1, 1, 0),
            (0, 0, 0, 0)
        ],
        3: [
            (0, 0, 0, 0),
            (0, 1, 1, 0),
            (0, 1, 1, 0),
            (0, 0, 0, 0)
        ]
    },
    2: {
        0: [
            (0, 0, 0, 0),
            (2, 2, 2, 2),
            (0, 0, 0, 0),
            (0, 0, 0, 0)
        ],
        1: [
            (0, 0, 2, 0),
            (0, 0, 2, 0),
            (0, 0, 2, 0),
            (0, 0, 2, 0)
        ],
        2: [
            (0, 0, 0, 0),
            (0, 0, 0, 0),
            (2, 2, 2, 2),
            (0, 0, 0, 0)
        ],
        3: [
            (0, 2, 0, 0),
            (0, 2, 0, 0),
            (0, 2, 0, 0),
            (0, 2, 0, 0)
        ]
    },
    3: {
        0: [
            (0, 0, 0, 0),
            (3, 3, 3, 0),
            (0, 3, 0, 0),
            (0, 0, 0, 0)
        ],
        1: [
            (0, 3, 0, 0),
            (3, 3, 0, 0),
            (0, 3, 0, 0),
            (0, 0, 0, 0)
        ],
        2: [
            (0, 3, 0, 0),
            (3, 3, 3, 0),
            (0, 0, 0, 0),
            (0, 0, 0, 0)
        ],
        3: [
            (0, 3, 0, 0),
            (0, 3, 3, 0),
            (0, 3, 0, 0),
            (0, 0, 0, 0)
        ]
    },
    4: {
        0: [
            (0, 0, 0, 0),
            (0, 4, 4, 0),
            (4, 4, 0, 0),
            (0, 0, 0, 0)
        ],
        1: [
            (4, 0, 0, 0),
            (4, 4, 0, 0),
            (0, 4, 0, 0),
            (0, 0, 0, 0)
        ],
        2: [
            (0, 0, 0, 0),
            (0, 4, 4, 0),
            (4, 4, 0, 0),
            (0, 0, 0, 0)
        ],
        3: [
            (4, 0, 0, 0),
            (4, 4, 0, 0),
            (0, 4, 0, 0),
            (0, 0, 0, 0)
        ]
    },
    5: {
        0: [
            (0, 0, 0, 0),
            (5, 5, 0, 0),
            (0, 5, 5, 0),
            (0, 0, 0, 0)
        ],
        1: [
            (0, 0, 5, 0),
            (0, 5, 5, 0),
            (0, 5, 0, 0),
            (0, 0, 0, 0)
        ],
        2: [
            (0, 0, 0, 0),
            (5, 5, 0, 0),
            (0, 5, 5, 0),
            (0, 0, 0, 0)
        ],
        3: [
            (0, 0, 5, 0),
            (0, 5, 5, 0),
            (0, 5, 0, 0),
            (0, 0, 0, 0)
        ]
    },
    6: {
        0: [
            (0, 0, 0, 0),
            (6, 6, 6, 0),
            (0, 0, 6, 0),
            (0, 0, 0, 0)
        ],
        1: [
            (0, 6, 0, 0),
            (0, 6, 0, 0),
            (6, 6, 0, 0),
            (0, 0, 0, 0)
        ],
        2: [
            (6, 0, 0, 0),
            (6, 6, 6, 0),
            (0, 0, 0, 0),
            (0, 0, 0, 0)
        ],
        3: [
            (0, 6, 6, 0),
            (0, 6, 0, 0),
            (0, 6, 0, 0),
            (0, 0, 0, 0)
        ]
    },
    7: {
        0: [
            (0, 0, 0, 0),
            (7, 7, 7, 0),
            (7, 0, 0, 0),
            (0, 0, 0, 0)
        ],
        1: [
            (7, 7, 0, 0),
            (0, 7, 0, 0),
            (0, 7, 0, 0),
            (0, 0, 0, 0)
        ],
        2: [
            (0, 0, 7, 0),
            (7, 7, 7, 0),
            (0, 0, 0, 0),
            (0, 0, 0, 0)
        ],
        3: [
            (0, 7, 0, 0),
            (0, 7, 0, 0),
            (0, 7, 7, 0),
            (0, 0, 0, 0)
        ]
    }
}


def display_board(board):
    """
    Displays the board on the screen.
    """
    for i in range(len(board)):
        for j in range(len(board[i])):
            pygame.draw.rect(dispSurf, (255,0,0) if int(board[i][j]) != 0 else (255,255,255), 
                pygame.Rect((j * 30) + 400, i * 30, 30, 30), 0)


def display_result(result):
    if result['outputs']['frame'] != -1:
        frame = frames[result['inputs']['currentPiece']][result['outputs']['frame']]
        col = result['outputs']['column']
        row = result['outputs']['row']
        for i in range(len(frame)):
            for j in range(len(frame[i])):
                actual_row = row + i
                actual_col = col + j
                if int(frame[i][j]) != 0:
                    pygame.draw.rect(dispSurf, (0,255,0), 
                        pygame.Rect((actual_col * 30) + 400, actual_row * 30, 30, 30), 0)


if __name__ == '__main__':
    random.seed()
    pygame.init()
    font = pygame.font.SysFont('Times New Roman', 20)
    s_font = pygame.font.SysFont('Times New Roman Bold', 50)

    clock = pygame.time.Clock()

    held = ((0, 0, 0, 0),
            (0, 0, 0, 0),
            (0, 0, 0, 0),
            (0, 0, 0, 0))
    dispSurf = pygame.display.set_mode((1200, 600))
    
    move_time = 0.5
    cur_move_time = 0

    with open('../training_data_raw/modified/flipped.json', 'r') as infile:
        inputs = json.load(infile)

    current_index = 0
    done = False
    while not done:
        delta_time = clock.tick() / 1000
        cur_move_time += delta_time
        if cur_move_time >= move_time:
            current_index += 1
            cur_move_time = 0
            print(current_index)
            if current_index >= len(inputs):
                done = True
                break

        for evt in pygame.event.get():
            if evt.type == pygame.QUIT:
                done = True

        dispSurf.fill((0, 0, 0))
        board = inputs[current_index]['inputs']['gameBoard']
        new_board = []
        for i in range(20):
            new_board.append(board[10*i:10*(i+1)])
        display_board(new_board)
        display_result(inputs[current_index])
        pygame.display.flip()

    pygame.display.quit()
