# Artificial Intelligence
# Tetris AI PyGame Visual Interface

import pygame, json
import pyTetris


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


def display_board():
    """
    Displays the board on the screen.
    """
    board = pyTetris.get_game_board()

    for i in range(len(board)):
        for j in range(len(board[i])):
            pygame.draw.rect(dispSurf, COLORS[int(board[i][j])], 
                pygame.Rect((j * 30) + 400, i * 30, 30, 30), 0)

def display_queued():
    """
    Display the queued pieces.
    """
    q = pyTetris.get_queued_pieces()
    txt = 'Next:'
    nxt_surf = font.render(txt, 0, (100, 200, 50))
    #dispSurf.blit(nxt_surf, (750, 225))
    if len(q) == 1: 
        for i in range(len(q[0])):
            for j in range(len(q[0][i])):
                if q[0][i] != 0:
                    pygame.draw.rect(dispSurf, COLORS[int(q[0][i][j])],
                        pygame.Rect((j * 30) + 710, (i * 30) + 100, 30, 30), 0)
    else:
        for i in range(len(q)):
            for j in range(len(q[i])):
                for k in range(len(q[i][j])):
                    if q[i][j][k] != 0:
                        pygame.draw.rect(dispSurf, COLORS[q[i][j][k]],
                            pygame.Rect((k * 30) + 150, (j * 30) + (i * 150) + 100, 30, 30), 0)


def display_held():
    """
    Displays the currently held piece.
    """
    held = pyTetris.get_held_piece()
    txt = 'Holding:'
    held_surf = font.render(txt, 0, (100, 200, 30))
    #dispSurf.blit(held_surf, )
    for i in range(len(held)):
        for j in range(len(held[i])):
            if held[i] != 0:
                pygame.draw.rect(dispSurf, COLORS[int(held[i][j])],
                pygame.Rect((j * 30) + 270, (i * 30) + 100, 30, 30), 0)


def display_score():
    """
    Displays the score
    """
    score = 2500
    
    txt = 'Score: ' + str(score)
    score_surf = s_font.render(txt, 0, (100, 200, 30))
    #dispSurf.blit(score_surf, (750, 75))


def get_input_scheme():
    with open('../../scripts/input_config.json', 'r') as infile:
        json_dict = json.load(infile)

    return json_dict[json_dict['currentConfig']]


if __name__ == '__main__':
    pygame.init()
    font = pygame.font.SysFont('Times New Roman', 20)
    s_font = pygame.font.SysFont('Times New Roman Bold', 50)

    clock = pygame.time.Clock()

    held = ((0, 0, 0, 0),
            (0, 0, 0, 0),
            (0, 0, 0, 0),
            (0, 0, 0, 0))
    dispSurf = pygame.display.set_mode((1200, 600))
    
    input_scheme = get_input_scheme()
    
    move_time = .15;
    cur_move_time = 0;

    done = False
    while not done:
        delta_time = clock.tick() / 1000
        pyTetris.tick(delta_time)

        for evt in pygame.event.get():
            if evt.type == pygame.QUIT:
                done = True
            elif evt.type == pygame.KEYDOWN:
                if evt.key == pygame.K_ESCAPE:
                    done = True
                if evt.key == input_scheme['left'] or evt.key == input_scheme['right']:
                    cur_move_time = move_time
                if evt.key == input_scheme['switch']:
                    held = pyTetris.switch_with_held_piece()
                if evt.key == input_scheme['ccw']:
                    pyTetris.rotate_piece_counter_clockwise()
                if evt.key == input_scheme['cw']:
                    pyTetris.rotate_piece_clockwise()
                if evt.key == input_scheme['hard']:
                    pyTetris.hard_drop()

        keys = pygame.key.get_pressed()
        if keys[input_scheme['soft']]:
            pyTetris.soft_drop()
        else:
            pyTetris.reset_soft_drop()
            
            
        if keys[input_scheme['left']]:
            cur_move_time += delta_time
            if cur_move_time >= move_time:
                cur_move_time = 0
                pyTetris.move_piece_left()
        elif keys[input_scheme['right']]:
            cur_move_time += delta_time
            if cur_move_time >= move_time:
                cur_move_time = 0
                pyTetris.move_piece_right()

        dispSurf.fill((0, 0, 0))
        display_board()
        display_queued()
        display_held()
        display_score()
        pygame.display.flip()

    pyTetris.quit()
    pygame.display.quit()
