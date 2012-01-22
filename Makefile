pflichtenheft:
	cd docs/Pflichtenheft/LaTeX \
	&& pdflatex -interaction scrollmode -no-shell-escape Pflichtenheft.tex \
	&& mv Pflichtenheft.pdf ..

handbuch:
	cd docs/Handbuch/LaTeX \
	&& pdflatex -interaction scrollmode -no-shell-escape Handbuch.tex \
	&& mv Handbuch.pdf ..

testprotokolle:
	cd docs/Testprotokolle/LaTeX \
	&& pdflatex -interaction scrollmode -no-shell-escape Testprotokolle.tex \
	&& mv Testprotokolle.pdf ..

dokumentation:
	doxygen doxygen.config
