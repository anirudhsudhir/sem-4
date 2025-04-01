build-container-image:
	docker build --platform=linux/amd64 -t ns2-container-image .

run-container:
	docker run -e DISPLAY=$$DISPLAY --rm -it ns2-container-image
