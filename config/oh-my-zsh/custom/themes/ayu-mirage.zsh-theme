setopt prompt_subst

PROMPT_VIMODE=${PROMPT_VIMODE:-I}

_ayu_prompt_git() {
	command git rev-parse --is-inside-work-tree >/dev/null 2>&1 || return

	local branch dirty
	branch=$(command git symbolic-ref --quiet --short HEAD 2>/dev/null || command git rev-parse --short HEAD 2>/dev/null) || return
	branch=${branch//\%/%%}

	[ -n "$(command git status --porcelain --ignore-submodules=dirty 2>/dev/null)" ] && dirty='*'
	printf ' %%F{#707a8c}git:%%f%%F{#d4bfff}%s%%f%%F{#f28779}%s%%f' "$branch" "$dirty"
}

zle-keymap-select() {
	case "$KEYMAP" in
	vicmd) PROMPT_VIMODE=N ;;
	*) PROMPT_VIMODE=I ;;
	esac
	zle reset-prompt
}

zle-line-init() {
	PROMPT_VIMODE=I
	zle reset-prompt
}

zle -N zle-keymap-select
zle -N zle-line-init

PROMPT='%F{#707a8c}╭─%f %F{#95e6cb}%n%f%F{#707a8c}@%f%F{#73d0ff}%m%f %F{#707a8c}in%f %F{#ffcc66}%~%f$(_ayu_prompt_git) %F{#707a8c}[%f%F{#d4bfff}${PROMPT_VIMODE}%f%F{#707a8c}]%f
%(?.%F{#95e6cb}.%F{#f28779})╰─❯%f '
RPROMPT='%(?..%F{#f28779}exit:%?%f )%F{#707a8c}%D{%H:%M}%f'
