void display(struct node* head)
{
	struct node *temp;
	temp=head;
	if(head==NULL)
	{
		printf("No flights\n");
	}
	else
	{
		while(temp->next!=NULL)
		{
			printf("%s\t%s\t%s\n",temp->date,temp->from,temp->to);
			temp=temp->next;
		}
		printf("%s\t%s\t%s\n",temp->date,temp->from,temp->to);
	}
}
