curl --silent https://api.github.com/repos/$1 | jq .stargazers_count
