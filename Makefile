
SHELL := /bin/bash
KEYBOARD ?= ergodox_ez
KEYMAP ?= rev2

help:
	@printf "Usage: make [target] [VARIABLE=value]\nTargets:\n"
	@grep -E '^[a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

build: ## Build layot
	@rm -rf out/*
	@printf "revision: $(KEYMAP)\n"
	@docker run \
		--env KEYBOARD=$(KEYBOARD) \
		--env KEYMAP=$(KEYMAP) \
		-v $(shell pwd)/out:/qmk_firmware/.build \
		-v $(shell pwd)/ergodox:/qmk_firmware/keyboards/$(KEYBOARD)/keymaps \
		--rm -it qmkfm/qmk_firmware make "${keyboard}:${keymap:+:$keymap}"
