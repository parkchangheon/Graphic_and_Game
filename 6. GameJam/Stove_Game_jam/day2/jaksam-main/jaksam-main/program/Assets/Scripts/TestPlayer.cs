using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestPlayer : MonoBehaviour
{
    Animator animator;
    Vector3 oldDir = Vector3.zero;
    // Start is called before the first frame update
    void Start()
    {
        TryGetComponent<Animator>(out animator);
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 dir = new Vector3(Input.GetAxisRaw("Horizontal"), Input.GetAxisRaw("Vertical"));

        if (oldDir != Vector3.zero && dir == Vector3.zero)
        {
            animator.SetFloat("OldX", oldDir.x);
            animator.SetFloat("OldY", oldDir.y);
            oldDir = Vector3.zero;
        }
        else
            oldDir = dir;

        animator.SetFloat("PositionX", dir.x);
        animator.SetFloat("PositionY", dir.y);

    }
}
