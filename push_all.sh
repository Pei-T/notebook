remote="origin_gitee/master origin_github/master"
date=$(date)
git add -A
git commit -m "${date}"
git push -u ${remote}