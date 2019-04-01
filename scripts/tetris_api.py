def get_game_board():
    """
    Gets the current state of the game board.

    The return value is a tuple of tuples:
        ((1, 2, 3, ...), (1, 2, 3, ...), (1, 2, 3, ...), (1, 2, 3, ...), ...)

    Each inner tuple represents a row of the game from top to bottom. Each
    number represents a certain type of block, which are color coded:

        Empty: 0 - White
        T: 1 - Purple
        I: 2 - Cyan
        O: 3 - Yellow
        L: 4 - Orange
        J: 5 - Blue
        S: 6 - Green
        Z: 7 - Red

    There will be 20 rows, each consisting of 10 blocks.

    :return: A tuple of tuples that represents the game board
    """
    pass


def get_held_piece():
    """
    Gets the piece that is currently being held aside. The piece is represented
    by a 4x4 tuple of tuples:

        ((1, 2, 3, 4), (1, 2, 3, 4), (1, 2, 3, 4), (1, 2, 3, 4))

    :return: a tuple of four tuples each containing four integers that represents
                the piece that is currently held
    """
    pass


def get_queued_pieces():
    """
    Returns a list of pieces that are currently queued for control. Each piece is
    represented by a 4x4 tuple of tuples:

        ((1, 2, 3, 4), (1, 2, 3, 4), (1, 2, 3, 4), (1, 2, 3, 4))

    At this point, there is only one queued piece, but there is a possibility that
    we will add more later on.

    :return: a list of tuples of four tuples each containing four integers that
                represent the pieces that are queued for control
    """
    pass


def move_piece_right():
    """
    Move the controlled piece to the right (if possible).
    :return: n/a
    """
    pass


def move_piece_left():
    """
    Move the controlled piece to the left (if possible).
    :return: n/a
    """
    pass


def rotate_piece_clockwise():
    """
    Rotates the controlled piece clockwise.
    :return: n/a
    """
    pass


def rotate_piece_counter_clockwise():
    """
    Rotates the controlled piece counter clockwise.
    :return: n/a
    """
    pass


def move_piece_down():
    """
    Accelerate the fall of the controlled piece.
    :return: n/a
    """
    pass


def switch_with_held_piece():
    """
    Switches the current piece with the piece that is being held. If there is no
    piece that is currently being held, then the current piece becomes the held piece
    and the piece that is next in the queue becomes the controlled piece.
    :return: n/a
    """
    pass
