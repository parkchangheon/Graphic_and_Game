
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    [SerializeField] private float speed;
    private Rigidbody2D body;
    private Animator anim;
    private bool grounded;

    private void Awake()
    {
        //Grab reference!
        body = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
    }

    private void Update()
    {
        float horizontalInput = Input.GetAxis("Horizontal");
        body.velocity = new Vector3(Input.GetAxis("Horizontal") * speed, body.velocity.y);

        //Flip Method
        if (horizontalInput >= 0.01f)
            transform.localScale = Vector3.one*5;

        else if (horizontalInput < -0.01f)
            transform.localScale = new Vector3(-1*5, 1*5, 1);

        //jump Method
        if (Input.GetKey(KeyCode.Space) && grounded)
            Jump();

        //set Animation Paramete
        anim.SetBool("IsRunning", horizontalInput != 0);
        anim.SetBool("Grounded", grounded);
    }

    private void Jump()
    {
        body.velocity = new Vector2(body.velocity.x, speed*4);
        anim.SetTrigger("Jump");
        grounded = false;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Ground")
            grounded = true;
    }
}
