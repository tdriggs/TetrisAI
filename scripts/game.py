# Artificial Intelligence
# Tetris AI PyGame Visual Interface

import pygame
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
    txt = "Next:"
    nxt_surf = font.render(txt, 0, (100, 200, 50))
    dispSurf.blit(nxt_surf, (50, 75))
    if len(q) == 1: 
        for i in range(len(q[0])):
            for j in range(len(q[0][i])):
                if q[0][i] != 0:
                    pygame.draw.rect(dispSurf, COLORS[int(q[0][i][j])],
                        pygame.Rect((j * 30) + 150, (i * 30) + 100, 30, 30), 0)
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
    txt = "Holding:"
    held_surf = font.render(txt, 0, (100, 200, 30))
    dispSurf.blit(held_surf, (750, 225))
    for i in range(len(held)):
        for j in range(len(held[i])):
            pygame.draw.rect(dispSurf, COLORS[int(held[i][j])],
                pygame.Rect((j * 60) + 800, (i * 60) + 250, 60, 60), 0)


def display_score():
    """
    Displays the score
    """
    score = 2500
    
    txt = "Score: " + str(score)
    score_surf = s_font.render(txt, 0, (100, 200, 30))
    dispSurf.blit(score_surf, (750, 75))


if __name__ == '__main__':
    pygame.init()
    font = pygame.font.SysFont("Times New Roman", 20)
    s_font = pygame.font.SysFont("Times New Roman Bold", 50)

    clock = pygame.time.Clock()

    held = ((0, 0, 0, 0),
            (0, 0, 0, 0),
            (0, 0, 0, 0),
            (0, 0, 0, 0))
    dispSurf = pygame.display.set_mode((1200, 600))
    
    done = False
    while not done:
        pyTetris.tick(clock.tick() / 1000)

        for evt in pygame.event.get():
            if evt.type == pygame.QUIT:
                done = True
            elif evt.type == pygame.KEYDOWN:
                if evt.key == pygame.K_LEFT:
                    pyTetris.move_piece_left()
                if evt.key == pygame.K_RIGHT:
                    pyTetris.move_piece_right()
                if evt.key == pygame.K_ESCAPE:
                    done = True
                if evt.key == pygame.K_z:
                    held = pyTetris.switch_with_held_piece()
                if evt.key == pygame.K_x:
                    pyTetris.rotate_piece_counter_clockwise()
                if evt.key == pygame.K_c:
                    pyTetris.rotate_piece_clockwise()
                if evt.key == pygame.K_v:
                    pyTetris.hard_drop()

        keys = pygame.key.get_pressed()
        if keys[pygame.K_DOWN]:
            pyTetris.soft_drop()
        else:
            pyTetris.reset_soft_drop()

        dispSurf.fill((0, 0, 0))
        display_board()
        display_queued()
        display_held()
        display_score()
        pygame.display.flip()

    pygame.display.quit()
