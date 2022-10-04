#/bin/zsh
sample_text="global variable"
fun1() {
    local sample_text="local variable"
    echo "function fun1 is executing"
    echo $sample_text
}
echo $sample_text
fun1
echo "script ended"
echo $sample_text
exit 0