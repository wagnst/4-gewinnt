#pragma once
//Board-Core: Create board, read&update field

struct board myboard;

int newBoard(struct board* target, unsigned int width, unsigned int height)
{
	//sanity check
	if (width<4 || height<4) {
		return 0;
	}

	//Initialize board
	target->width = width;
	target->height = height;
	target->numberOfFields = width*height;
	target->content = malloc(target->numberOfFields * sizeof(char));

	//abort if memory allocation failed
	if (target->content == NULL) {
		return 0;
	}

	//board is ready, now clear it
	clearBoard(target);
}

void clearBoard(struct board* target) {
	//fills the whole board with space chars
	int i = 0;
	while (i < target->numberOfFields) {
		char* field = (target->content+i);
		*field = 'p';
		printf("%i:%c\n",(int)field,*field);
		i++;
	}
}
