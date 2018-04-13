git diff-index --quiet HEAD --
if [ $? -ne 0 ]; then
    echo 'Please stash your current changes before running update-master.sh!'
    exit 1
fi

# Bookmark the place we came from.
TOP_LEVEL=$(git rev-parse --show-toplevel)
pushd "$TOP_LEVEL" >/dev/null
LAST_REVISION=$(git symbolic-ref --short -q HEAD)
if [ -z "$LAST_REVISION" ]; then
    LAST_REVISION=$(git rev-parse HEAD)
fi

# Check out the new upstream master.
git fetch upstream master
git checkout upstream/master

# Perform the carriage-return-removal.
AFFECTED_FILES=$(git grep --files-with-matches $'\r' lib include)
echo "$AFFECTED_FILES" | xargs -- sed -i -e $'s/\r//'
find lib include -name '*-e' -delete
echo "$AFFECTED_FILES" | xargs -- git add --

# Copy this script from old master to new master.
git checkout master -- update-master.sh
git add update-master.sh

# Commit all our changes, i.e., both the carriage-return-removal and this script.
git checkout -B master
git commit -m 'Remove carriage returns from lib/ and include/. NFC.'

# Return to our bookmarked place.
git checkout "$LAST_REVISION"
popd >/dev/null
