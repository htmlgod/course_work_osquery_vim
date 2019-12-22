openIssues=$(curl --silent \
	"https://api.github.com/search/issues?q=repo:$1+type:issue+state:open" \
	| jq .total_count)
echo $1 has ${openIssues} open issues
closedIssues=$(curl --silent \
	"https://api.github.com/search/issues?q=repo:$1+type:issue+state:closed" \
	| jq .total_count)
echo $1 has ${closedIssues} closed issues
