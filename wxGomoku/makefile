CC=g++
TARGET=wxGomoku
MODULES=core controller ui
OBJDIR=obj
OBJS=GomokuBoard.o GomokuGame.o GomokuAI.o GlobalLoader.o wxGomokuMain.o wxGomokuApp.o wxGomokuEvents.o wxGUIFrame.o wxGomokuCanvas.o
INC=-Iinclude `wx-config --cppflags`
LIBS=-lpthread `wx-config --libs`
CTAGS=--std=c++11 -O2 -Wall -m64
LTAGS=-s -m64

$(TARGET):: $(OBJDIR) $(MODULES)
		@echo "Linking......"
		$(CC) $(OBJDIR)/*.o -o $(TARGET) $(LIBS) $(LTAGS)

$(OBJDIR):
		mkdir $(OBJDIR)

core::
		@echo "Compiling Core..."
		$(CC) -c core/GomokuBoard.cpp -o $(OBJDIR)/GomokuBoard.o $(INC) $(CTAGS)
		$(CC) -c core/GomokuGame.cpp -o $(OBJDIR)/GomokuGame.o $(INC) $(CTAGS)
		$(CC) -c core/GomokuAI.cpp -o $(OBJDIR)/GomokuAI.o $(INC) $(CTAGS)

controller::
		@echo "Compiling Controller..."
		$(CC) -c controller/GlobalLoader.cpp -o $(OBJDIR)/GlobalLoader.o $(INC) $(CTAGS)
		$(CC) -c controller/GomokuBot.cpp -o $(OBJDIR)/GomokuBot.o $(INC) $(CTAGS)
		$(CC) -c controller/wxGomokuMain.cpp -o $(OBJDIR)/wxGomokuMain.o $(INC) $(CTAGS)
		$(CC) -c controller/wxGomokuApp.cpp -o $(OBJDIR)/wxGomokuApp.o $(INC) $(CTAGS)

ui::
		@echo "Compiling UI..."
		$(CC) -c ui/wxGomokuEvents.cpp -o $(OBJDIR)/wxGomokuEvents.o $(INC) $(CTAGS)
		$(CC) -c ui/wxGUIFrame.cpp -o $(OBJDIR)/wxGUIFrame.o $(INC) $(CTAGS)
		$(CC) -c ui/wxGomokuCanvas.cpp -o $(OBJDIR)/wxGomokuCanvas.o $(INC) $(CTAGS)

.PHONY: clean
clean:
		@echo "Cleaning..."
		rm -rf $(OBJDIR)
		rm $(TARGET)

