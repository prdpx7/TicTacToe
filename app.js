var mat = ["___", "___", "___"];
//light box is highlighter for winning diagonal/line
var light_box;
var bot_win = false, player_win = false;
$(document).ready(function(){
  $('.btn').click(function(){
      var id = $(this).attr('id');
      if($("#"+id).attr('src')==="./C_TextMode/empty_tile.png"){
        var ridx = int_div(id,10);
        mat[ridx] = mat[ridx].replaceAt(id%10,"X");
      }
      else {
        return false;
      }
      chk = processData();
      //console.log(mat);
      for(var i = 0; i < 3; ++i){
        for(var j = 0; j < 3; ++j){
          var id = "" + i + j;
          if(mat[i][j] === "X"){
            $("#"+id).attr("src","./C_TextMode/x_tile.png");
          }
          else if(mat[i][j] === "O"){
            $("#"+id).attr("src","./C_TextMode/o_tile.png");
          }
          else{
            $("#"+id).attr("src","./C_TextMode/empty_tile.png");
          }
        }
      }
      var win_img ;
      if(player_win){
        win_img = "./C_TextMode/user_won.png";
      }
      else if(bot_win){
        win_img = "./C_TextMode/bot_won.jpg";
      }

      if(light_box){
      for(var i = 0; i < light_box.length; ++i){
        //console.log(light_box[i]);
        $("#"+light_box[i]).attr("src",win_img);
      }
    }
      if(player_win){

        alert("You win");
        window.location.reload();
      }
      else if(bot_win){
        alert("Bot wins");
        window.location.reload();
      }
      else if(chk == false){
        for(var i = 0; i < 9; ++i){
          $("#"+int_div(i,3) + i%3).attr("src","./C_TextMode/fork_me.jpg");
        }
        alert("Draw");
        window.location.reload();
      }


    });

});
String.prototype.replaceAt=function(index, character) {
        return this.substr(0, index) + character + this.substr(index+character.length);
}
function int_div(x,y){
  return Math.floor(x/y);
}

function chk_empty_cell(mat) {

    for(var i = 0; i < 3; ++i){
        idx = mat[i].indexOf('_');
        if(idx != -1){
            return i*10+idx;
        }
    }
    return -1;
}
function win(mat) {

   if(mat[0][0] === mat[1][1] && mat[1][1] === mat[2][2] && mat[1][1] != '_'){
    // console.log("dig");
      light_box = ["00","11","22"];
       return true;
     }
    if(mat[0][2] === mat[1][1] && mat[1][1] === mat[2][0] && mat[1][1] !== '_'){
      //  console.log("inv_dig");
      light_box = ["02","11","20"];
       return true;
     }
    for(var i = 0; i < 3; ++i) {
        var mat_flag = true;
        var tr_mat_flag = true;// transpose mat flag
        var tmp_light_box = [""+i+0],tmp_tr_light_box = [""+0+i];
        for(var j = 1; j < 3; ++j) {
            if(mat[j][i] === "_" || mat[j][i] !== mat[j-1][i])
                tr_mat_flag = false;
            else{
              tmp_tr_light_box.push("" + j + i);
            }
            if(mat[i][j] === "_" || mat[i][j] !== mat[i][j-1])
                mat_flag = false;
            else{
              tmp_light_box.push(""+i+j);
            }
        }

        if(mat_flag || tr_mat_flag){
          if(mat_flag){
            light_box = tmp_light_box;
          }
          else{
            console.log("possible");
            light_box = tmp_tr_light_box;
          }

          return true;
        }
    }
    return false;
}
function find_next_move(player, flag) {
    // here flag == true indicate i'm looking for winning in next move and flag == false means i'm looking to stop other player to win
    var dig = "",inv_dig = "";

    for(var i=0; i < 3; ++i){
        dig += mat[i][i];
        inv_dig += mat[i][2-i];
    }

    var pre_win_moves ;
    if(player === "X") {
        pre_win_moves = ["_XX", "X_X", "XX_"];
    }
    else{
        pre_win_moves = ["_OO", "O_O", "OO_"];
    }

    var tmp_mat = ["", "", ""];
    for(var i = 0; i < 3; ++i){
        var tmp = "";
        for(var j = 0; j < 3; ++j){
            tmp = tmp + mat[j][i];
        }
        tmp_mat[i] = tmp;
    }
    //console.log(pre_win_moves);
    //console.log(tmp_mat);
    if(mat[1][1] === '_')
        return 11;
    if(player === "X") {
        //X__
        //___
        //__X
        if(!flag &&  mat[0] === "X__" && tmp_mat[2] === "__X"){
            if(tmp_mat[1] === "_O_")
            return 01;
            else
            return 02;
          }
        if(!flag && mat[2] === "__X" && tmp_mat[0] === "X__"){
            if(tmp_mat[1] === "_O_")
              return 01;
            else
              return 20;
          }
    }
    else {
        //O__
        //___
        //__O
        if(!flag &&  mat[0] === "O__" && tmp_mat[2] === "__O"){
            if(tmp_mat[1] === "X_")
              return 01;
            else
              return 02;
          }
        if(!flag && mat[2] === "__O" && tmp_mat[0] === "O__"){
            if(tmp_mat[1] === "_X_")
              return 01;
            else
              return 20;
          }
    }
  //  console.log("player:"+player,"pre_win_moves: ",pre_win_moves);
    for(var i = 0; i < 3; ++i){
        if(pre_win_moves[i] === dig)
            return i*10 + i;
        if(pre_win_moves[i] === inv_dig)
            return i*10 + 2-i;
        for(var j = 0; j < 3; ++j) {
            if(pre_win_moves[j] === mat[i])
                return i*10 + j;
            if(pre_win_moves[j] === tmp_mat[i])
                return j*10 + i;
        }
    }
    return chk_empty_cell(mat);
}


function processData() {
    // now mat will have only 3X3 string matrix
    if(win(mat)){
      console.log(mat);
      player_win = true;
      return true;
    }
    var idx = find_next_move("O",true);
    if(idx != -1) {
        ridx = int_div(idx,10);
        mat[ridx] = mat[ridx].replaceAt(idx%10,"O");
        if(win(mat)) {
          bot_win = true;
            return true;
        }
        mat[ridx] = mat[ridx].replaceAt(idx%10,'_');
    }
    idx = find_next_move("X", false);
    if(idx == -1)
      return false;

    ridx = int_div(idx,10);
    mat[ridx] = mat[ridx].replaceAt(idx%10,"O");
    return true;
}
