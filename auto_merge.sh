#!/bin/bash

# 获取冲突文件列表
conflict_files=$(git diff --name-only --cached)

# 对每个冲突文件执行
for file in $conflict_files; do
    git checkout --theirs $file
    git add $file
done

# 继续变基
git rebase --continue