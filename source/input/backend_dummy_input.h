#ifndef BACKEND_DUMMY_INPUT_H
#define BACKEND_DUMMY_INPUT_H

int InitDummyInput();
void UpdateDummyInput();
int DummyKeyMap(json_t* js, char* c);
int GetButtonDummy(int port, int button);

#endif
