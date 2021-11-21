using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class SpriteAnim : MonoBehaviour
{
    [SerializeField]
    List<Sprite> sprites;
    Image Animimage;
    IEnumerator Start()
    {
        Animimage = GetComponent<Image>();
        while (true)
        {
            for(int i = 0; i < sprites.Count; i++)
            {
                Animimage.sprite = sprites[i];
                yield return new WaitForSeconds(0.5f);
            }
        }
        
    }


}
