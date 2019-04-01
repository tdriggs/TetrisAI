#Artificial Intelligence
#Tetris AI PyGame Visual Interface

import pygame
# from tetris_api import *

#20 rows: 10 blocks each
#200 block grid
ROWS = 20
COLUMNS = 10


#0=Empty-White,1=T-Purple,2=I-Cyan,3=O-Yellow,4=L-Orange,5=J-Blue,6=S-Green,7=Z-Red
COLOR = (
         (255,255,255),
         (200,0,200),
         (0,150,200),
         (250,250,0),
         (250,150,0),
         (0,0,255),
         (0,255,0),
         (255,0,0)
         )

#For Testing Purposes, can be deleted later.
dummyBoard = (
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,0,0,0,0,0,0,0),
                (0,0,0,1,1,1,0,0,0,0),
                (1,0,0,0,1,0,0,4,0,0),
                (1,1,7,7,0,4,4,4,3,3),
                (1,7,7,2,2,2,2,0,3,3)
             )

Q1 = ((0,0,0,0),
      (0,1,1,1),
      (0,0,1,0),
      (0,0,0,0))

Q2 = ((0,2,0,0),
      (0,2,0,0),
      (0,2,0,0),
      (0,2,0,0))

Q3 = ((0,0,0,0),
      (0,0,0,4),
      (4,4,4,4),
      (0,0,0,0))

Q4 = (Q1,Q2,Q3)


def display_board():
    """
    Displays the board in its current state.
    board = get_game_board()"""

    #delete this code once API properly implemented
    board = dummyBoard

    #Keep this code
    for i in range(ROWS):
        for j in range(COLUMNS):
            pygame.draw.rect(dispSurf,COLOR[board[i][j]],
                             pygame.Rect((j*30)+400,i*30,30,30),0)

def display_next():
    """Displays the next Piece"""

    #Use This Code when API finished.
    """q = get_queued_pieces()
    txt = "Next:"
    nxt_surf = font.render(txt,0,(100,200,50))
    dispSurf.blit(nxt_surf,(50,75))
    if len(q)==1: 
        for i in range(len(q[0])):
            for j in range(len(q[0][i])):
                if q[0][i] != 0:
                    pygame.draw.rect(dispSurf,COLOR[q[0][i][j]],
                             pygame.Rect((j*30)+150,(i*30)+100,30,30),0)
    else:
        for i in range(len(q)):
            for j in range(len(q[i])):
                for k in range(len(q[i][j])):
                    if q[i][j][k] !=0:
                        pygame.draw.rect(dispSurf,COLOR[q[i][j][k]],
                             pygame.Rect((k*30)+150,(j*30)+ (i*150)+ 100,30,30),0)"""

    #delete this code once API properly implemented
    for i in range(len(Q4)):
        for j in range(len(Q4[i])):
            for k in range(len(Q4[i][j])):
                pygame.draw.rect(dispSurf,COLOR[Q4[i][j][k]],
                                 pygame.Rect((k*30)+100,(j*30)+(i*150)+100,30,30),0)
    txt = "Next:"
    nxt_surf = font.render(txt,0,(100,200,50))
    dispSurf.blit(nxt_surf,(50,75))

def display_held():
    """Displays the currently held piece"""
    #delete this code once API properly implemented
    held = ((0,0,0,0),
            (0,0,0,0),
            (0,0,7,7),
            (0,7,7,0))
    #Use this code when API finished.
    """held = get_held_piece()"""
    txt = "Holding:"
    held_surf = font.render(txt,0,(100,200,30))
    dispSurf.blit(held_surf,(750,225))
    for i in range(len(held)):
        for j in range(len(held[i])):
            pygame.draw.rect(dispSurf,COLOR[held[i][j]],
                             pygame.Rect((j*60)+800,(i*60)+250,60,60),0)

def display_score():
    """Displays the score"""
    #API doesn't have get_score function, so I'm not sure if this is necessary or not.
    #Delete this code when API properly implemented.
    score = 2500
    
    #Use this code when API finished
    """txt = "Score:" + get_score()"""
    txt = "Score: " + str(score)
    score_surf = s_font.render(txt, 0, (100, 200, 30))
    dispSurf.blit(score_surf, (750, 75))


if __name__ == '__main__':
    pygame.init()
    font = pygame.font.SysFont("Times New Roman", 20)
    s_font = pygame.font.SysFont("Times New Roman Bold", 50)
    held = ((0, 0, 0, 0),
            (0, 0, 0, 0),
            (0, 0, 0, 0),
            (0, 0, 0, 0))
    dispSurf = pygame.display.set_mode((1200, 600))
    done = False

    while not done:
        evt = pygame.event.poll()
        if evt.type == pygame.QUIT:
            done = True
        elif evt.type == pygame.KEYDOWN:
            if evt.key == pygame.K_ESCAPE:
                done = True
            if evt.key == pygame.K_w:
                held = switch_with_held_piece()
            if evt.key == pygame.K_a:
                move_piece_left()
            if evt.key == pygame.K_s:
                move_piece_down()
                move_piece_right()
            if evt.key == pygame.K_d:
                move_piece_right()
            if evt.key == pygame.K_q:
                rotate_piece_counter_clockwise()
            if evt.key == pygame.K_e:
                rotate_piece_clockwise()

        dispSurf.fill((0, 0, 0))
        display_board()
        display_next()
        display_held()
        display_score()
        pygame.display.flip()

    pygame.display.quit()
