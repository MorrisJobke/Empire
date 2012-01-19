pflichtenheft:
	cd docs/Pflichtenheft/LaTeX \
	&& pdflatex -interaction scrollmode -no-shell-escape Pflichtenheft.tex \
	&& mv Pflichtenheft.pdf ..

testprotokolle:
	cd docs/Testprotokolle/LaTeX \
	&& pdflatex -interaction scrollmode -no-shell-escape Testprotokolle.tex \
	&& mv Testprotokolle.pdf ..
