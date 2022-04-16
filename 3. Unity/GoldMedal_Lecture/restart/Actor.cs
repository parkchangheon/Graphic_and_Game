using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Actor : MonoBehaviour
{
    
    int id;
    public string name;
    string title;
    string weapon;
    float strength;
    public int level = 10;

    public string Talk()
    {
        return "대화를 걸다";
    }


    public string HasWeapon()
    {
        return weapon;
    }

    public void LevelUp()
    {
        level += 1;
        Debug.Log("레벨이 올랐습니다!!");
    }
}
