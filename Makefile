pflichtenheft:
	cd docs/Pflichtenheft/LaTeX \
	&& pdflatex -interaction scrollmode -no-shell-escape Pflichtenheft.tex \
	&& pdflatex -interaction scrollmode -no-shell-escape Pflichtenheft.tex \
	&& mv Pflichtenheft.pdf ..
