JAVAC = javac
JAVA  = java

all: MainWindow.class

MainWindow.class: *.java
	$(JAVAC) *.java

run: all
	$(JAVA) MainWindow

clean:
	rm -f *.class
