/* copyright 2020 firecrow silvernight, licensed under the wtfpl see LICENSE file */

void handle_case(int pass_fail, char *msg, int val, char *example){
  if(pass_fail){
    printf("\x1b[32mPASS:");
  }else{
    printf("\x1b[31mFAIL:");
  }
  printf("%s, val:%d, example:%s\x1b[0m\n", msg, val, example);
}
